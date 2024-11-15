#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../inputPlugins/MoveCommandPlugin/MoveCommandPlugin.h"
#include "../../src/service/TourneyService/CorePluginBattleCommand.h"
#include "../../IoC/IoC.h"


TEST(TestMoveCommandPlugin, test_loard)
{
    extern IoC* ioc;
    CorePluginBattleCommand core;

    MoveCommandPlugin plugin;
    /*plugin.InitPlugin(ioc);
    auto strTypr = plugin.GetType();
    plugin.Load();*/

    int sdfsd = 0;


}
