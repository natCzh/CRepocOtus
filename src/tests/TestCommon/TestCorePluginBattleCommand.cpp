#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <boost/any.hpp>

#include "IoC/IoC.h"
#include "service/TourneyService/CorePluginBattleCommand.h"
#include "service/Message.h"

#include <thread>
#include <chrono>

TEST(TestCorePluginBattleCommand, test)
{
    CorePluginBattleCommand core;
/////////////////// getNewGame
/// Добавление новой игры
    std::vector<unsigned long long> typeObjsVect{1};
    boost::any typeObjsAny = typeObjsVect;
    std::vector<unsigned long long> idObjsVect{0};
    boost::any idObjsAny = idObjsVect;

    UObject_Ptr uobj_ptr = std::make_shared<Message>();
    uobj_ptr->setProperty("typeObjs", typeObjsAny);
    uobj_ptr->setProperty("idObjsNewGame", idObjsAny);

    unsigned int idGame = core.getNewGame(uobj_ptr);
/////////////////// message addCommandForGame CommandInterpret.StartMove
/// Добавление команды CommandInterpret.StartMove в игру

    std::map<std::string, boost::any> argsMap;
    int velPr = 1;
    argsMap["velocity"] = boost::any(velPr);

    boost::any idGameAny = idGame;
    std::string cmd = "CommandInterpret.StartMove";
    boost::any cmdAny = cmd;
    std::shared_ptr<Message> mes_ptr = std::make_shared<Message>();
    mes_ptr->setProperty("id.Game", idGameAny);
    mes_ptr->setProperty("id.Object", idGameAny);
    mes_ptr->setProperty("id.Sender", idGameAny);
    mes_ptr->setProperty("TypeCommand", cmdAny);
    mes_ptr->setProperty("args", argsMap);

    core.addCommandForGame(mes_ptr);
 /////////////////// startNewGame
 /// Старт игры
    core.startNewGame(0, 0);

/////////////////// message addCommandForGame CommandInterpret.Rotate
/// Добавление команды CommandInterpret.Rotate в игру

    std::shared_ptr<Message> mes_ptr_Rot = std::make_shared<Message>();
    std::string cmd2 = "CommandInterpret.Rotate";
    boost::any cmdAny2 = cmd2;
    mes_ptr_Rot->setProperty("TypeCommand", cmdAny2);
    mes_ptr_Rot->setProperty("id.Game", idGameAny);
    mes_ptr_Rot->setProperty("id.Object", idGameAny);
    mes_ptr_Rot->setProperty("id.Sender", idGameAny);

    std::map<std::string, boost::any> argsMapRot;
    int dirAng = 1;
    argsMapRot["directionAngular"] = boost::any(dirAng);
    mes_ptr_Rot->setProperty("args", argsMapRot);

    core.addCommandForGame(mes_ptr_Rot);

/////////////////// message addCommandForGame CommandInterpret.StopMove
/// Добавление команды CommandInterpret.StopMove в игру
    std::string cmdStop = "CommandInterpret.StopMove";
    boost::any cmdStopAny = cmdStop;
    std::shared_ptr<Message> mes_ptr_Stop = std::make_shared<Message>();
    mes_ptr_Stop->setProperty("id.Game", idGameAny);
    mes_ptr_Stop->setProperty("id.Object", idGameAny);
    mes_ptr_Stop->setProperty("id.Sender", idGameAny);
    mes_ptr_Stop->setProperty("TypeCommand", cmdStopAny);
    mes_ptr_Stop->setProperty("args", argsMap);

    core.addCommandForGame(mes_ptr_Stop);

/////////////////// message addCommandForGame CommandInterpret.Rotate через 3 сек
/// Добавление команды CommandInterpret.Rotate в игру через 3 сек
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);

    std::shared_ptr<Message> mes_ptr_Rot2 = std::make_shared<Message>();
    mes_ptr_Rot2->setProperty("TypeCommand", cmdAny2);
    mes_ptr_Rot2->setProperty("id.Game", idGameAny);
    mes_ptr_Rot2->setProperty("id.Object", idGameAny);
    mes_ptr_Rot2->setProperty("id.Sender", idGameAny);

    std::map<std::string, boost::any> argsMapRot2;
    dirAng = -1;
    argsMapRot2["directionAngular"] = boost::any(dirAng);
    mes_ptr_Rot2->setProperty("args", argsMapRot2);

    core.addCommandForGame(mes_ptr_Rot2);

/////////////////// message addCommandForGame CommandInterpret.Shot 3 раза через 3 сек
/// Добавление команды CommandInterpret.Rotate в игру через 3 сек
    std::shared_ptr<Message> mes_ptr_Shot = std::make_shared<Message>();
    std::string cmdShot = "CommandInterpret.Shot";
    boost::any cmdShotAny = cmdShot;
    mes_ptr_Shot->setProperty("TypeCommand", cmdShotAny);
    mes_ptr_Shot->setProperty("id.Game", idGameAny);
    mes_ptr_Shot->setProperty("id.Object", idGameAny);
    mes_ptr_Shot->setProperty("id.Sender", idGameAny);


    core.addCommandForGame(mes_ptr_Shot);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    core.addCommandForGame(mes_ptr_Shot);
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    core.addCommandForGame(mes_ptr_Shot);




    core.addCommandForGame(mes_ptr_Shot);
    core.addCommandForGame(mes_ptr_Shot);
    core.addCommandForGame(mes_ptr_Shot);
/////////////////// stopGame
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(30s);
    core.stopGame(0, 0);




    int n = 0;
}



