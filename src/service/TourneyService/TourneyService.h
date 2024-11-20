#ifndef _TOURNEY_SERVICE_H_
#define _TOURNEY_SERVICE_H_

#include <map>
#include <atomic>

#include "service/TourneyService/SpaceBattle.h"

class TourneyService
{
public:

    // тут запускает EndPoint ловить исключения



    // Класс то образом принимает запрос, конвертирует в json -> string -> IMessage -> InterpretCommand


protected:
	SpaceBattle										spaceBattle;
};

#endif /* _TOURNEY_SERVICE_H_ */
