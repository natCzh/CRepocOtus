#ifndef _TOURNEY_SERVICE_H_
#define _TOURNEY_SERVICE_H_

#include <map>
#include <atomic>

#include "service/TourneyService/EventLoop.h"

class TourneyService
{
public:

	// тут запускает EndPoint ловить исключения 

protected:

	static std::atomic<size_t>									gameId;
	// хэш таблица - ид игры, EventLoop с игрой
	std::map<size_t, EventLoop>									hashMapGames;
};

#endif /* _TOURNEY_SERVICE_H_ */