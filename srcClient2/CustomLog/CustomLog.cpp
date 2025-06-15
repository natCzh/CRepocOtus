#include "CustomLog.h"
#include "qcolor.h"
#include "qfont.h"
#include "qplaintextedit.h"

CustomLog::CustomLog(QObject *parent)
    : QObject{parent}{}

void CustomLog::SetLogData(QString message, MessageType type)
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    if (type == MessageType::FedFormat)
        format.setForeground(QColor(20, 100, 150));
    else if (type == MessageType::Signals)
        format.setForeground(QColor(70, 60, 200));
    else if (type == MessageType::Overflows)
        format.setForeground(QColor(70, 150, 70));
    else if (type == MessageType::Sources)
        format.setForeground(QColor(200, 130, 60));
    else if (type == MessageType::Clear)
        format.setForeground(QColor(160, 200, 40));
    else if (type == MessageType::Error)
        format.setForeground(QColor(255, 0, 0));
    else if (type == MessageType::FileNotChoosen)
        format.setForeground(QColor(80, 80, 80));
    else if (type == MessageType::Default)
    {
        format.setFontWeight(QFont::Black);
        format.setForeground(QColor(0,0,0));
    }

    dynamic_cast<QPlainTextEdit*>(logWidget)->setCurrentCharFormat(format);
    emit LogMessage(message);
    format.setForeground(QColor(0,0,0));
    format.setFontWeight(QFont::Normal);
    dynamic_cast<QPlainTextEdit*>(logWidget)->setCurrentCharFormat(format);
}

void CustomLog::setLogWidget(QWidget* logWidget)
{
    this->logWidget = logWidget;
}
