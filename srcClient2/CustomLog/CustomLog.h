#ifndef CUSTOMLOG_H
#define CUSTOMLOG_H

#include "MessageType.h"
#include <QObject>

class CustomLog : public QObject
{
    Q_OBJECT
public:
    explicit CustomLog(QObject *parent = nullptr);
    void setLogWidget(QWidget* logWidget);
    void SetLogData(QString message, MessageType type);
signals:
    void LogMessage(QString message);
private:
    //указатель на виджет логгера
    QWidget * logWidget;
};

#endif // CUSTOMLOG_H
