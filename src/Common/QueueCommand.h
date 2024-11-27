#ifndef _QUEUE_COMMAND_H
#define _QUEUE_COMMAND_H

#include <queue>
#include <memory>
#include <vector>
#include <mutex>

#include <QDebug>

#include "Command/ICommand.h"

// TODO сделать класс IQueue и от него наследоваться !!!!!!!!!!
class QueueCommand
{
public:
    QueueCommand(int maxSize_)
        : flagDel(0)
        , maxSize(maxSize_)
    {}

    virtual ~QueueCommand(){}

    std::shared_ptr<ICommand> GetCurrentCommand()
    {
        qDebug() << "get queue";
         // LogQueue();
        if (flagDel)
        {
            queueCommand.erase(queueCommand.begin());
            flagDel = 0;
        }

        if (!queueCommand.size())
            return nullptr;
        else
        {
            flagDel = 1;
            maxSize--;
            return queueCommand.front();
        }
    }

    void Push(std::shared_ptr<ICommand> commandCur)
    {
        queueCommand.push_back(commandCur);
        qDebug() << "push queue";
        //LogQueue();
    }

protected:
    void LogQueue()
    {
        unsigned int iterNumb = 0;
        for (auto iter = queueCommand.begin(); iter != queueCommand.end(); iter++)
        {
            qDebug() << "[" << iterNumb << "] - " << QString::fromStdString(iter->get()->GetType());
            iterNumb++;
        }

        qDebug() << "";
    }

private:
    int												flagDel = 0;
    unsigned int									maxSize =  50;

    std::vector<std::shared_ptr<ICommand> >			queueCommand;
};


#endif _QUEUE_COMMAND_H
