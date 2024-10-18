# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include <memory>

#include "../src/StatesQueueProcessing.h"
#include "../src/Command.h"
#include "../src/queueProcessing.h"

using namespace testing;

// проверяет, что после команды hard stop, поток завершается
TEST(TestStatesQueueProcessing, testHardStop)
{
	CommandEmpty commandEmpty;
	HardStop commandHardStop;
	ICommand_Ptr commandCurEmpty = std::make_shared<CommandEmpty>(commandEmpty);
	ICommand_Ptr commandCurHardStop = std::make_shared<HardStop>(commandHardStop);
	
	SimpleStatesQueueProcessing simpleState;
	ICommandStatesQueueProcessing *simpleState_Ptr = new SimpleStatesQueueProcessing(simpleState);

	// начальное состояние Обычное - после hardStop прекарщается работа, и выкидывается исключение
	queueProcessing processing(simpleState_Ptr);
	processing.pushCommand(commandCurEmpty);
	processing.pushCommand(commandCurHardStop);
	EXPECT_THROW(processing.execute(), CommandException);

	// начальное состояние Обычное - работа прекращается без исключения, так как все команжы выполнились
	simpleState_Ptr = new SimpleStatesQueueProcessing(simpleState);
	queueProcessing processing1(simpleState_Ptr);
	processing1.pushCommand(commandCurEmpty);
	processing1.pushCommand(commandCurEmpty);
	EXPECT_NO_THROW(processing1.execute());
}

class SimpleStatesQueueProcessing_MOCK: public SimpleStatesQueueProcessing
{
public:

	SimpleStatesQueueProcessing_MOCK()
	{}

	virtual ~SimpleStatesQueueProcessing_MOCK() {}

	bool handle(queueProcessing *m)
	{
		bool result = SimpleStatesQueueProcessing::handle(m);

		return result;
	}

	std::string GetType() override
	{
		return "SimpleStatesQueueProcessing_MOCK";
	}

public:
	std::string				typeState;
};

// проверяет, что после команды MoveToCommand поток переходит на обработку Команд с помощью состояния MoveTo
TEST(TestStatesQueueProcessing, testMoveToCommand)
{
	CommandEmpty commandEmpty;
	MoveToCommand commandMoveTo;
	ICommand_Ptr commandCurEmpty = std::make_shared<CommandEmpty>(commandEmpty);
	ICommand_Ptr commandCurMoveTo = std::make_shared<MoveToCommand>(commandMoveTo);
	
	SimpleStatesQueueProcessing_MOCK simpleState;
	ICommandStatesQueueProcessing *simpleState_Ptr = new SimpleStatesQueueProcessing_MOCK(simpleState);

	// начальное состояние Обычное - после hardStop прекарщается работа, и выкидывается исключение
	queueProcessing processing(simpleState_Ptr);
	processing.pushCommand(commandCurEmpty);
	processing.pushCommand(commandCurMoveTo);
	processing.execute();
	EXPECT_EQ(processing.GetTypeStates(), "MoveToStatesQueueProcessing");
}

// проверяет, что после команды RunCommand, поток переходит на обработку Команд с помощью состояния "Обычное" 
TEST(TestStatesQueueProcessing, testRunCommand)
{
	CommandEmpty commandEmpty;
	RunCommand commandRunCommand;
	ICommand_Ptr commandCurEmpty = std::make_shared<CommandEmpty>(commandEmpty);
	ICommand_Ptr commandCurRunCommand = std::make_shared<RunCommand>(commandRunCommand);
	
	MoveToStatesQueueProcessing initState;
	MoveToStatesQueueProcessing *initState_Ptr = new MoveToStatesQueueProcessing(initState);

	// начальное Move_To
	queueProcessing processing(initState_Ptr);
	processing.pushCommand(commandCurEmpty);
	processing.pushCommand(commandCurRunCommand);
	processing.execute();
	EXPECT_EQ(processing.GetTypeStates(), "SimpleStatesQueueProcessing");
}