#include "service/TourneyService/TourneyService.h"

idGameAndThread TourneyService::CreateNewGame(size_t scopeId, std::vector<unsigned long long> idObjs, std::vector<unsigned long long> idObjsType)
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
        initObjVect.push_back(InitObjectGame(fileNameConfig, idObjsType[iterNumb], idObjs[iterNumb], scopeId));
        initObjVect.back().Execute();
        iterNumb++;
    }

    return resultId;
}

void TourneyService::StartNewGame(idGameAndThread idGame)
{
    spaceBattle.StartGame(idGame.threadId); // TODO тут мы запускаем все игры в этом потоке
}

void TourneyService::AddCommandToGame(idGameAndThread idGame, size_t scopeId, std::shared_ptr<Message> m)
{
    std::shared_ptr<QueueCommand> queue = spaceBattle.GetQueueGame(idGame);
    endPoint.process(m, scopeId, queue);
}
