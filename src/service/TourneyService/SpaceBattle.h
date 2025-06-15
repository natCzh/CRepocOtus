#ifndef _SPACE_BATTLE_H_
#define _SPACE_BATTLE_H_

#include <map>
#include <atomic>

#include "service/TourneyService/EventLoop.h"
#include "Command/ICommand.h"
#include "service/IdGameAndThread.h"
#include "service/InitObjectGame.h"
#include "service/InitGameClassCommon.h"

// сущность, которая содержит игры, очередь игр, запускает их и тд
// о скоупах ничего не знает, только пользует
class SpaceBattle
{
public:
    SpaceBattle(size_t maxThreadId_)
        : maxThreadId(maxThreadId_)
    {}

    /// @brief Создание новой игры
    /// @param[in] cmdInit - команда инициализации игры
    /// @param[in] scopeId
    idGameAndThread CreateNewGame(ICommand_Ptr cmdInit, size_t scopeId); // тут надо что-то передать для инициализацииы

	void StartGame(size_t id);
	void StopGame(size_t id);

    /// @brief Получение очереди команд игры
    /// @param[in] idGame
    /// @param[out] очередь команд для игры
    std::shared_ptr<QueueCommand> GetQueueGame(idGameAndThread idInf)
    {
        return hashMapGames[idInf.threadId]->getQueueGame(idInf.idGame);
    }

protected:
    size_t getThreadId()
	{
        return gameThreadId++;
	}

private:

    static std::atomic<size_t>									gameThreadId;
    size_t                                                      maxThreadId;                      // кол-во потоков
    // хэш таблица - ид потока, EventLoop с играми
	std::map<size_t, std::shared_ptr<EventLoop> >				hashMapGames;
};

#endif /* _SPACE_BATTLE_H_ */
