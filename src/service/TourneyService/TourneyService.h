#ifndef _TOURNEY_SERVICE_H_
#define _TOURNEY_SERVICE_H_

#include "service/TourneyService/SpaceBattle.h"
#include "EndPoint/EndPointTourneyS.h"
#include "Command/CommandEmpty.h"
#include "service/InitGameClassCommon.h"
#include "service/InitObjectGame.h"

class TourneyService
{
public:

    TourneyService()
        : spaceBattle(1)
        , fileNameConfig("C:/Natalia/otus/les5/CRepocOtus/src/service/initGameObject.json")
    {}

    virtual ~TourneyService(){}

    // тут запускает EndPoint ловить исключения

    void process()
    {}


    /// [in] idObjs - ид объектов, idObjsType - ид типов для этих объектов(все это с маршрутизатора приходит)
    idGameAndThread CreateNewGame(size_t scopeId, std::vector<unsigned long long> idObjs, std::vector<unsigned long long> idObjsType);

    /// Начать игру
    void StartNewGame(idGameAndThread idGame);

    void StopGame(idGameAndThread idGame);



    // Класс то образом принимает запрос, конвертирует в json -> string -> IMessage -> InterpretCommand

    /// Добавим команду в игру
    void AddCommandToGame(idGameAndThread idGame, size_t scopeId, std::shared_ptr<Message> m);

    void LogGame(idGameAndThread idGame, std::string &logData);


protected:
    SpaceBattle                                                       spaceBattle;
    EndPoint                                                          endPoint;
    std::string                                                       fileNameConfig;
    std::vector<InitGameClassCommon>                                  initCommonVect;
    std::vector<InitObjectGame>                                       initObjVect;
};

#endif /* _TOURNEY_SERVICE_H_ */
