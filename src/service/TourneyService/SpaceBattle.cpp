#include "service/TourneyService/SpaceBattle.h"

#include "Exception/SpaceBattleException.h"
#include "Command/GameCommand.h"

std::atomic<size_t> SpaceBattle::gameThreadId(0);

// TODO !!!!!!!!!! это должно быть где то вверху
// std::deque<size_t> idsScopesGame;			// ид скоупов всех игр - идут на пару с collection, -1 - если это не игра

// TODO скоуп под игру уже должен быть создан !!!!!!!!!
idGameAndThread SpaceBattle::CreateNewGame(ICommand_Ptr cmdInit, size_t scopeId)
{
    size_t newThreadId = getThreadId();
    if (newThreadId >= maxThreadId)
    {
        gameThreadId = 0;
        newThreadId = 0;
    }
    if (hashMapGames.find(newThreadId) == hashMapGames.end())
        hashMapGames.insert(std::make_pair(newThreadId, std::make_shared<EventLoop>()));
    size_t idCurGame = hashMapGames[newThreadId]->addNewGame(cmdInit, scopeId);

    idGameAndThread resultStruct{newThreadId, idCurGame};

    return resultStruct;
}

void SpaceBattle::StartGame(size_t id)
{
	if (hashMapGames.find(id) == hashMapGames.end())
		throw SpaceBattleException("Gameid isn't exist");
	hashMapGames[id]->startLoop();

}

void SpaceBattle::StopGame(size_t id)
{
	if (hashMapGames.find(id) == hashMapGames.end())
		throw SpaceBattleException("Gameid isn't exist");
	hashMapGames[id]->stop();
}
