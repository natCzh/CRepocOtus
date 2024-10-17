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
	

	// начальное состояние Обычное - после hardStop прекарщается работа, и выкидывается исключение
	queueProcessing processing;
	processing.pushCommand(commandCurEmpty);
	processing.pushCommand(commandCurHardStop);
	EXPECT_THROW(processing.execute(), CommandException);

	// начальное состояние Обычное - работа прекращается без исключения, так как все команжы выполнились
	queueProcessing processing1;
	processing1.pushCommand(commandCurEmpty);
	processing1.pushCommand(commandCurEmpty);
	EXPECT_NO_THROW(processing1.execute());
}