#include "service/TourneyService/SpaceBattle.h"

#include "Exception/SpaceBattleException.h"

std::atomic<size_t> SpaceBattle::gameId(0);

size_t SpaceBattle::CreateNewGame()
{
	size_t newIdGame = getNextGameId();
	hashMapGames.insert(std::make_pair(newIdGame, std::make_shared<EventLoop>()));

	// TODO проинициализировать командами !!!!!!!!!!

	return newIdGame;
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

void SpaceBattle::AddCommandForObject(size_t idGame, size_t idObj, ICommand_Ptr cmd)
{
	if (hashMapGames.find(idGame) == hashMapGames.end())
		throw SpaceBattleException("Gameid isn't exist");

	hashMapGames[idGame]->setICommandToGameObject(idObj, cmd);
}

