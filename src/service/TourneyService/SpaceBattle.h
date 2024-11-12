#ifndef _SPACE_BATTLE_H_
#define _SPACE_BATTLE_H_

#include <map>
#include <atomic>

#include "service/TourneyService/EventLoop.h"
#include "Command/ICommand.h"

// сущность, которая содержит игры, очередь игр, запускает их и тд
class SpaceBattle
{
public:
	SpaceBattle() {}

	size_t CreateNewGame(); // тут надо что-то передать для инициализацииы

	void StartGame(size_t id);
	void StopGame(size_t id);
	void AddCommandForObject(size_t idGame, size_t idObj, ICommand_Ptr cmd);

protected:
	size_t getNextGameId()
	{
		return gameId++;
	}

private:

	static std::atomic<size_t>									gameId;
	// хэш таблица - ид игры, EventLoop с игрой
	std::map<size_t, std::shared_ptr<EventLoop> >				hashMapGames;
};

#endif /* _SPACE_BATTLE_H_ */