﻿
# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include "src/IoC.h"
#include "src/Exception/IoCException.h"
#include "src/Command/MoveCommand.h"


TEST(TestIoC, test_scope)
{
	MoveCommand curMove;
	ICommand_Ptr ICurrentCommand = std::make_shared<MoveCommand>(curMove);
	inputParamsIocRegister params;
	params.strCommand = "MoveCommand";
	params.command = ICurrentCommand;

	IoC ioc;
	// скоупа нету, поэтому эксепшен

	std::string key = "IoC.Register";
	EXPECT_THROW(ioc.Resolve<ICommand>(key, (void*)(&params)), IoCException);

	// добавляем новый скоуп
	size_t idScope = 0;
	EXPECT_NO_THROW(ioc.Resolve<ICommand>("Scopes.New", static_cast<void*>(&idScope)));
	EXPECT_NO_THROW(ioc.Resolve<ICommand>("Scopes.Current", static_cast<void*>(&idScope)));

}