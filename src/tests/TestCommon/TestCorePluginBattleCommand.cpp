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
    std::vector<unsigned long long> typeObjsVect{1};
    boost::any typeObjsAny = typeObjsVect;
    std::vector<unsigned long long> idObjsVect{0};
    boost::any idObjsAny = idObjsVect;

    UObject_Ptr uobj_ptr = std::make_shared<Message>();
    uobj_ptr->setProperty("typeObjs", typeObjsAny);
    uobj_ptr->setProperty("idObjsNewGame", idObjsAny);

    unsigned int idGame = core.getNewGame(uobj_ptr);
/////////////////// message addCommandForGame CommandInterpret.StartMove

    std::map<std::string, boost::any> argsMap;
    int velPr = 1;
    int dirAng = 1;
    argsMap["velocity"] = boost::any(velPr);
    argsMap["directionAngular"] = boost::any(dirAng);

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
 ///
    core.startNewGame(0, 0);

/////////////////// message addCommandForGame CommandInterpret.Rotate

    std::shared_ptr<Message> mes_ptr_Rot = std::make_shared<Message>();
    std::string cmd2 = "CommandInterpret.Rotate";
    boost::any cmdAny2 = cmd2;
    mes_ptr_Rot->setProperty("TypeCommand", cmdAny2);
    mes_ptr_Rot->setProperty("id.Game", idGameAny);
    mes_ptr_Rot->setProperty("id.Object", idGameAny);
    mes_ptr_Rot->setProperty("id.Sender", idGameAny);

    core.addCommandForGame(mes_ptr);

/////////////////// message addCommandForGame CommandInterpret.Rotate

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10s);

/////////////////// stopGame
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(300s);
    core.stopGame(0, 0);



    int n = 0;

}



