#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <boost/any.hpp>

#include "IoC/IoC.h"
#include "service/TourneyService/CorePluginBattleCommand.h"
#include "service/Message.h"

TEST(TestCorePluginBattleCommand, test)
{
    CorePluginBattleCommand core;

    Message mes;

    std::vector<unsigned long long> typeObjsVect{1};
    boost::any typeObjsAny = typeObjsVect;
    mes.setProperty("typeObjs", typeObjsAny);


    std::vector<unsigned long long> idObjsVect{1};
    boost::any idObjsAny = idObjsVect;
    mes.setProperty("idObjsNewGame", idObjsAny);

    UObject_Ptr message_ptr = std::make_shared<Message>(mes);


    core.getNewGame(message_ptr);

    int n = 0;

}



