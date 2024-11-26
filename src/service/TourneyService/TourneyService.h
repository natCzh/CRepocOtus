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
    {

         // endPoint.process(UObject_Ptr m, size_t scopeId, std::shared_ptr<QueueCommand> queue)






    }


    /// [in] idObjs - ид объектов, idObjsType - ид типов для этих объектов(все это с маршрутизатора приходит)
    idGameAndThread CreateNewGame(size_t scopeId, std::vector<unsigned long long> idObjs, std::vector<unsigned long long> idObjsType)
    {
        ICommand_Ptr cmdRepeat = std::make_shared<CommandEmpty>();
        idGameAndThread resultId = spaceBattle.CreateNewGame(cmdRepeat, scopeId); // тту можно заменить команду на инициализацию, например какого то игрока

        InitGameClassCommon initGameCur(idObjs, scopeId);
        initCommonVect.push_back(initGameCur);
        std::shared_ptr<InitGameClassCommon> initGame = std::make_shared<InitGameClassCommon>(initCommonVect.back());
        initGame->Execute();
        size_t iterNumb = 0;
        for (auto iter = idObjs.begin(); iter != idObjs.end(); iter++)
        {
            InitObjectGame initGameCur(fileNameConfig, idObjsType[iterNumb], idObjs[iterNumb], scopeId);
            initObjVect.push_back(std::make_shared<InitObjectGame>(initGameCur));
            initObjVect.back()->Execute();
            iterNumb++;
        }

        return resultId;
    }



    // Класс то образом принимает запрос, конвертирует в json -> string -> IMessage -> InterpretCommand


protected:
    SpaceBattle                                                       spaceBattle;
    EndPoint                                                          endPoint;
    std::string                                                       fileNameConfig;
    std::vector<InitGameClassCommon>                                  initCommonVect;
    std::vector<std::shared_ptr<InitObjectGame> >                     initObjVect;
};

#endif /* _TOURNEY_SERVICE_H_ */
