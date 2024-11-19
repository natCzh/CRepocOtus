#ifndef _EVENT_LOOP_H_
#define _EVENT_LOOP_H_

#include <thread>
#include <functional>

#include "src/Common/ThreadDeque.h"
#include "src/Command/ICommand.h"
#include "src/CommonLib/CommandException.h"
#include "src/service/ExceptionHendler.h"
#include "src/Exception/MessageTourneySException.h"

class EventLoop
{
public:

	EventLoop()
		: flagStop(false)
		, waitMilliSec(1)
		, threadCur(nullptr)
		, gameObjectId(0)
	{
		behavior = std::bind(&EventLoop::behaviorCommon, this);
	}

	EventLoop(ExceptionHendler &excHendler_, int waitMilliSec_ = 10)
		: flagStop(false)
		, waitMilliSec(waitMilliSec_)
		, excHendler(excHendler_)
		, gameObjectId(0)
	{
		//this->threadCur = std::thread{ &CommandCollection::loop, this };
	}

	~EventLoop()
	{
		stop();
	}

	void setExceptionHandler(ExceptionHendler &excHendler_);

	void stop();
	void startLoop();
	void loop();
	void behaviorCommon();
	void softStop();
	void behaviorSS();

    // TODO !!! проверить перед этим обязательно в вызове делается установка текущего скоупа
    /// @brief Создание новой команды в очередь, не игры
    /// @param[in] cmdInit - команда инициализации игры
    void add(ICommand_Ptr cmd);
    /// @brief Создание новой игры
    /// @param[in] cmdInit - команда инициализации игры
    /// @param[in] scopeId
    size_t addNewGame(ICommand_Ptr cmdInit, size_t scopeIdCur);

    std::shared_ptr<ThreadDeque<ICommand_Ptr> > getCollectionGame()
    {
        return std::make_shared<ThreadDeque<ICommand_Ptr> >(collection);
    }

    /// @brief Получение очереди команд игры
    /// @param[in] idGame
    /// @param[out] очередь команд для игры
    std::shared_ptr<QueueCommand> getQueueGame(size_t idGame)
    {
        return queueGame[idGame];
    }


protected:

    size_t getNextGameId()
    {
        return gameId++;
    }

private:

    ThreadDeque<ICommand_Ptr>                                       collection;
    bool                                                            flagStop;				// флаг остановки, false - работаем
    int                                                             waitMilliSec;			// кол-во миллисекунд, которые ждем команду
    ExceptionHendler                                                excHendler;
    std::thread                                                     *threadCur;
    std::function<void()>                                           behavior;
    // параметры для игр
    static size_t                                                   gameId;
    std::unordered_map<size_t, std::shared_ptr<QueueCommand> >      queueGame;              // ид игры - очередь игры
    int                                                             maxSizeQueueGame;       // максимальное кол-во команд в очереди игры
    unsigned long long                                              quantGame;              // кол-во секунд сессии 1 прохода игры
};

#endif /* _EVENT_LOOP_H_ */
