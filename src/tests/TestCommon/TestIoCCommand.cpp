#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IoC/IoC.h"
#include "IoC/IoCException.h"
#include "Command/ICommand.h"

#include <typeinfo>
#include <functional>

class MoveCommandMock : public ICommand
{
public:
	MoveCommandMock() {}
	virtual ~MoveCommandMock() {}
	MoveCommandMock(const MoveCommandMock &other)
	{}

	MOCK_METHOD0(GetType, std::string());
	MOCK_METHOD0(Execute, void());
};

class TestMock
{
public:

	TestMock()
		: mockMove() {}
	virtual ~TestMock() {}

	MoveCommandMock mockMove;
	int x = 0;

	ICommand_Ptr reg()
	{
		std::shared_ptr<ICommand> cmd = std::make_shared<MoveCommandMock>(mockMove);
		x = 1;
		return cmd;
	}

	int reg1()
	{
		return x;
	}
};

TEST(TestIoCCommand, commonIoC_Register_ICommand_Ptr_void)
{
	IoC ioc;
	TestMock testMock;

	std::function<ICommand_Ptr()> func = std::bind(&TestMock::reg, &testMock);
	//EXPECT_CALL(testMock.mockMove, Execute()).WillOnce(testing::Return());
	// регистрация
	ioc.Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr()>>("IoC.Register", "MoveCommandMock", func)->Execute();
	// получение
 	ICommand_Ptr cur = ioc.Resolve<ICommand_Ptr>("MoveCommandMock");
	cur->Execute();
	EXPECT_EQ(testMock.x, 1);
}

TEST(TestIoCCommand, commonIoC_Register_int_void)
{
	IoC ioc;
	TestMock testMock1;
	std::function<int(void)> func = std::bind(&TestMock::reg1, testMock1);
	// регистрация
	ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int()> >("IoC.Register", "A", func)->Execute();
	// получение
	int cur = ioc.Resolve<int>("A");
	EXPECT_EQ(cur, 0);

	// проверка на эксепшен
	//int cur1 = ioc.Resolve<int>("B");
	EXPECT_THROW(ioc.Resolve<int>("B"), IoCException);
}

TEST(TestIoCCommand, commonIoC_Register_exception)
{
	IoC ioc;
	TestMock testMock1;
	std::function<int(void)> func = std::bind(&TestMock::reg1, testMock1);
	// регистрация
	ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int()> >("IoC.Register", "A", func)->Execute();

	// проверка на эксепшен
	//int cur1 = ioc.Resolve<int>("B");
	EXPECT_THROW(ioc.Resolve<int>("B"), IoCException);
}

int regFuncVarTemplate(int x)
{
	return x;
}

TEST(TestIoCCommand, commonIoC_Register_int_int)
{
	IoC ioc;
	std::function<int(int)> func1 = &regFuncVarTemplate;
	int x = 2;

	// регистрация
	auto cmds = ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int(int)>, int >("IoC.Register", "A", func1, x);
	cmds->Execute();

	// получение
	int c = ioc.Resolve<int>("A", x);
	EXPECT_EQ(c, 2);
	x = 3;
	c = ioc.Resolve<int>("A", x);
	EXPECT_EQ(c, 3);
}


