#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IoC/IoC.h"
#include "service/TourneyService/CorePluginBattleCommand.h"
#include "service/InitObjectGame.h"
#include "service/InitGameClassCommon.h"

extern IoC* ioc;
TEST(TestInitObjectGame, test)
{
    CorePluginBattleCommand core;
    std::string fileName = "C:/Natalia/otus/les5/CRepocOtus/src/service/initGameObject.json";
    unsigned long long idObjType = 1;
    size_t idScope = 0;
    unsigned long long idObj = 1;
    std::vector<unsigned long long> idObjsVect;
    idObjsVect.push_back(idObj);
    InitGameClassCommon initGame(idObjsVect, idScope);
    InitObjectGame initObj(fileName, idObjType, idObj, idScope);
    initGame.Execute();
    initObj.Execute();
    int d = 0;
    d++;
}
