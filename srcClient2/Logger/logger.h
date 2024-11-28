#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"

#include <QtDebug>
#include <QFile>
#include <QPlainTextEdit>

class LOGGERSHARED_EXPORT Logger : public QObject
{
    Q_OBJECT

public:
    explicit Logger(qint64 sizeForSwap = 1024*1024, int filesCount = 2, QString logFileName = "logFile.txt", QString filterFileName = "filterFile.txt");
    virtual ~Logger();

	Q_PROPERTY(QString LastLogMessage READ LastLogMessage WRITE setLastLogMessage NOTIFY newLogMessageStr)

	QString LastLogMessage() const;

    QObject *createLogWidget(QWidget* parent = nullptr);
    void setLogWidget(QObject* widget);

public slots:
    void unsetLogWidget();

	void setLastLogMessage(QString value);

signals:
    void newLogMessage(QVariant);
    void newLogMessageStr(QString value);

private:
    static QObject* s_logWidget;

	QString  m_lastMessage;

    static QString getCurrentFileName();
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static QScopedPointer<QFile>   s_logFile;

    static qint64   s_sizeForSwap;

    static int      s_filesCount;
    static int      s_currentFile;

    static QString  s_logFileName;
};

#endif // LOGGER_H
