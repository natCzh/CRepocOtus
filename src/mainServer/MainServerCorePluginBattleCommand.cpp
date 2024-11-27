#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "mainServer/MainServerCorePluginBattleCommand.h"

#include "service/TourneyService/CorePluginBattleCommand.h"

using grpc::Status;

MainServerCorePluginBattleCommand::MainServerCorePluginBattleCommand()
    : core(std::make_shared<CorePluginBattleCommand>())
{}

grpc::Status MainServerCorePluginBattleCommand::StartNewGame(grpc::ServerContext* context, const StartNewGameRequest* request, StartNewGameReply* response)
{
    /// должны вернуть ид игры
    UObject_Ptr uobj_ptr = std::make_shared<Message>();
    unsigned int idObj = request->idobj();
    boost::any idObjAny = idObj;
    uobj_ptr->setProperty("id.Sender", idObjAny);
    uobj_ptr->setProperty("id.Object", request->idobj());
    // тут это будет читаться с json TODO переделать !!!!!
    std::vector<unsigned long long> typeObjsVect{1};
    uobj_ptr->setProperty("typeObjs", request->idobj());
    std::vector<unsigned long long> idObjsVect{0}; // тут это будет читаться с json TODO переделать !!!!!
    boost::any idObjsAny = idObjsVect;
    uobj_ptr->setProperty("idObjsNewGame", idObjsAny);

    unsigned long long idGame = (unsigned long long)core->getNewGame(uobj_ptr);
    core->startNewGame(idGame, 0);

    response->set_resultcheck(true);
    response->set_idgame(idGame);

    return Status::OK;
}

grpc::Status MainServerCorePluginBattleCommand::AddCommandGame(grpc::ServerContext* context, const AddCommandGameRequest* request, AddCommandGameReply* response)
{
    std::shared_ptr<Message> mes_ptr = std::make_shared<Message>();
    boost::any idGameAny = request->idgame();
    mes_ptr->setProperty("id.Game", idGameAny);
    boost::any idObjAny = request->idobj();
    mes_ptr->setProperty("id.Object", idGameAny);
    boost::any idSenderAny = request->idsender();
    mes_ptr->setProperty("id.Sender", idGameAny);
    boost::any cmdAny = request->typecommand();
    mes_ptr->setProperty("TypeCommand", cmdAny);

    std::map<std::string, boost::any> argsMap;
    getMapFromStr(request->args(), argsMap);
    /*int velPr = 1;
    argsMap["velocity"] = boost::any(velPr);
    mes_ptr->setProperty("args", argsMap);*/
    core->addCommandForGame(mes_ptr);

    return Status::OK;
}

grpc::Status MainServerCorePluginBattleCommand::StopGame(grpc::ServerContext* context, const StopGameRequest* request, StopGameReply* response)
{
    size_t idGame = (size_t)request->idgame();
    core->stopGame(idGame, 0);

    return Status::OK;
}

void MainServerCorePluginBattleCommand::getMapFromStr(std::string str, std::map<std::string, boost::any> &mapCur)
{
//     std::string dsfsd = "velocity, 1;directionAngular, 1";
    const char* const delimeters = ";";

    char* strCur = std::strtok(str.data(), delimeters);

    const char* const delimeters2 = ", ";
    char* strCur2;
    std::string str1 = strCur;
    std::vector<std::string> words;
    strCur2 = std::strtok(str1.data(), delimeters2);
    while (strCur2 != nullptr)
    {
        words.push_back(strCur2);
        strCur2 = std::strtok(nullptr, delimeters2);
    }

    mapCur[words[0]] = std::stoi(words[1]);
}
