#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IoC/IoC.h"
#include "Command/ParseJSonCommand.h"

TEST(TestSpaceBattle, test)
{
	std::string nameCommand = "Movement";
	std::string filenameConfig = "../src/initFile/initParamsObject.json";
	size_t idScope = 0;
	ParseJsonCommand parse(nameCommand, filenameConfig, idScope);
	parse.Execute();

	int sdfsd = 0;

}
