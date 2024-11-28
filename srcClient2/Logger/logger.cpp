#include "logger.h"

#include <QLoggingCategory>
#include <QMutex>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>

Logger* s_logger = nullptr;
QObject* Logger::s_logWidget = nullptr;
QScopedPointer<QFile> Logger::s_logFile;
static QMutex s_mutex;

qint64 Logger::s_sizeForSwap = 1024*1024;
int Logger::s_filesCount = 2;
int Logger::s_currentFile = 0;
QString Logger::s_logFileName = "logFile.txt";

Logger::Logger(qint64 sizeForSwap, int filesCount, QString logFileName, QString filterFileName) :
    QObject()
{
    s_logger = this;

    s_sizeForSwap = sizeForSwap;
    s_filesCount = filesCount;
    s_logFileName = logFileName;

    s_currentFile = 0;


	QFile filterFile(filterFileName);

	if (filterFile.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream textStream(&filterFile);
		QString filters = textStream.readAll();

		filterFile.close();

		QLoggingCategory::setFilterRules(filters);
	}

    s_logFile.reset(new QFile(getCurrentFileName()));

    s_logFile.data()->resize(0);
    s_logFile.data()->open(QFile::Append | QFile::Text);

    qInstallMessageHandler(myMessageOutput);

    QString strDebug(    "%{if-debug}[%{time yyyy-MM-dd h:mm:ss.zzz} D] %{category}: %{message} %{endif}");
    QString strInfo (     "%{if-info}[%{time yyyy-MM-dd h:mm:ss.zzz} I] %{category}: %{message} %{endif}");
    QString strWarn (  "%{if-warning}[%{time yyyy-MM-dd h:mm:ss.zzz} W] %{category}: %{message} %{endif}");
#ifdef WIN32
	QString strCrit(  "%{if-critical}[%{time yyyy-MM-dd h:mm:ss.zzz} C] %{category}: %{message} %{function} in %{file}:%{line} %{endif}");
	QString strFatal(  "  %{if-fatal}[%{time yyyy-MM-dd h:mm:ss.zzz} F] %{category}: %{message} %{function} in %{file}:%{line} %{endif}");
#else
    QString strCrit ( "%{if-critical}[%{time yyyy-MM-dd h:mm:ss.zzz} C] %{category}: %{message} %{function} in %{file}:%{line} \n %{backtrace depth=10} %{endif}");
    QString strFatal(    "%{if-fatal}[%{time yyyy-MM-dd h:mm:ss.zzz} F] %{category}: %{message} %{function} in %{file}:%{line} \n %{backtrace depth=10} %{endif}");
#endif // !WIN32

    qSetMessagePattern( strDebug + strInfo + strWarn + strCrit + strFatal );
}

Logger::~Logger()
{
	QMutexLocker locker(&s_mutex);

    qInstallMessageHandler(0);

    s_logWidget = nullptr;
    s_logger = nullptr;
}

QString Logger::LastLogMessage() const
{
	return m_lastMessage;
}

QObject *Logger::createLogWidget(QWidget *parent)
{
    if(s_logWidget == nullptr)
    {
        QPlainTextEdit* widget = new QPlainTextEdit(parent);

        QFont font("Courier");
        font.setPixelSize(10);
        widget->setFont(font);


        s_logWidget = widget;

        QObject::connect(this, SIGNAL(newLogMessageStr(QString)),  s_logWidget, SLOT(appendPlainText(QString)));

        QObject::connect(s_logWidget, SIGNAL(destroyed(QObject*)), this, SLOT(unsetLogWidget()));

        return s_logWidget;
    }

    return nullptr;
}

void Logger::setLogWidget(QObject *widget)
{
    s_logWidget = widget;

    if(QMetaObject::checkConnectArgs(SIGNAL(newLogMessage(QVariant)), SLOT(append(QString))))
        QObject::connect(this, SIGNAL(newLogMessage(QVariant)),  s_logWidget, SLOT(append(QString)));
    else if(QMetaObject::checkConnectArgs(SIGNAL(newLogMessage(QVariant)), SLOT(append(QVariant))))
        QObject::connect(this, SIGNAL(newLogMessage(QVariant)), s_logWidget, SLOT(append(QVariant)));

    QObject::connect(widget, SIGNAL(destroyed(QObject*)), this, SLOT(unsetLogWidget()));
}

void Logger::unsetLogWidget()
{
    QObject::disconnect(s_logWidget);

    s_logWidget = nullptr;
}

void Logger::setLastLogMessage(QString value)
{
	m_lastMessage = value;

	emit newLogMessage(value);
	emit newLogMessageStr(value);
}

QString Logger::getCurrentFileName()
{
    QFileInfo fileInfo(s_logFileName);

    return fileInfo.absoluteDir().absoluteFilePath(fileInfo.baseName() + QString("_%1").arg(s_currentFile) + "." + fileInfo.suffix());
}

void Logger::myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString formattedMsg =  qFormatLogMessage(type, context, msg);
    QString formattedMsgWithEndl = formattedMsg + "\n";
	
    switch (type)
    {
    case QtInfoMsg:     fprintf(stdout, formattedMsgWithEndl.toLocal8Bit().constData()); fflush(stdout); break;
    case QtDebugMsg:    fprintf(stdout, formattedMsgWithEndl.toLocal8Bit().constData()); fflush(stdout); break;
    case QtWarningMsg:  fprintf(stderr, formattedMsgWithEndl.toLocal8Bit().constData()); fflush(stderr); break;
    case QtCriticalMsg: fprintf(stderr, formattedMsgWithEndl.toLocal8Bit().constData()); fflush(stderr); break;
    case QtFatalMsg:    fprintf(stderr, formattedMsgWithEndl.toLocal8Bit().constData()); fflush(stderr); break;
    }

	QMutexLocker locker(&s_mutex);
    if(s_logFile.data()->size() > s_sizeForSwap)
    {
        s_logFile.data()->close();

        s_currentFile = (s_currentFile + 1) % s_filesCount;

        s_logFile.reset(new QFile(getCurrentFileName()));

        s_logFile.data()->resize(0);
        s_logFile.data()->open(QFile::Append | QFile::Text);
    }

    QTextStream out(s_logFile.data());
    out << formattedMsgWithEndl;
    out.flush();

    if(s_logger)
    {
		s_logger->setLastLogMessage(formattedMsg);
    }
}
