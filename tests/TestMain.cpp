# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include "../src/main.h"
#include "src/Command.h"
#include "src/HandlerFactory.h"
#include "src/BootStrapHendler.h"

using namespace testing;


TEST(TestCommandExecute, test1_1)
{
	int x = mainCommand();
}

TEST(TestCommandExecute, test_p4)
{
	CommandLogger commandCur("strExecute");
	commandCur.Execute();
}

TEST(TestCommandExecute, test_p5)
{
	QueueCommand qCommand(10);
	CommandLogger commandCur("strExecute");
	HandlerLogQueue queue(qCommand);
	std::exception e;

	ICommand_Ptr com_ptr = std::make_shared<CommandLogger>(commandCur);

	ICommand_Ptr command_cur_ptr = queue.process(com_ptr, e);
	bool flagCast;
	if (auto comCur_ptr = dynamic_cast<CommandAddQueueEnd*>(command_cur_ptr.get()))
		flagCast = true;
	else
		flagCast = false;

	ASSERT_TRUE(flagCast);
}

TEST(TestCommandExecute, test_p6)
{
	QueueCommand qCommand(10);
	CommandLogger commandLog("strExecute_test_p6");
	CommandRepeat commandCur(qCommand, std::make_shared<CommandLogger>(commandLog));
	commandCur.Execute();
}

TEST(TestCommandExecute, test_p7)
{
	QueueCommand qCommand(10);
	CommandLogger commandCur("strExecute_test_p7");
	HandlerRepeat queue(qCommand);
	std::exception e;

	ICommand_Ptr com_ptr = std::make_shared<CommandLogger>(commandCur);

	ICommand_Ptr command_cur_ptr = queue.process(com_ptr, e);
	bool flagCast;
	if (auto comCur_ptr = dynamic_cast<CommandRepeat*>(command_cur_ptr.get()))
		flagCast = true;
	else
		flagCast = false;

	ASSERT_TRUE(flagCast);
}

TEST(TestCommandExecute, test_p8)
{
	QueueCommand qCommand(10);
	CommandLogger commandCur("strExecute_test_p8");
	HandlerRepeatAndLog queue(qCommand);
	std::exception e;

	ICommand_Ptr com_ptr = std::make_shared<CommandLogger>(commandCur);
	ICommand_Ptr command_cur_ptr = queue.process(com_ptr, e);
	bool flagCast;
	if (auto comCur_ptr = dynamic_cast<CommandRepeat*>(command_cur_ptr.get()))
		flagCast = true;
	else
		flagCast = false;

	ICommand_Ptr command_cur_ptrRepeat = queue.process(command_cur_ptr, e);
	bool flagCast2;
	if (auto comCur_ptr = dynamic_cast<CommandLogger*>(command_cur_ptrRepeat.get()))
		flagCast2 = true;
	else
		flagCast2 = false;

	ASSERT_TRUE(flagCast && flagCast2);
}

TEST(TestCommandExecute, test_p9)
{
	QueueCommand qCommand(10);
	CommandLogger commandCur("strExecute_test_p8");
	HandlerRepeatTwoAndLog queue(qCommand);
	std::exception e;

	ICommand_Ptr com_ptr = std::make_shared<CommandLogger>(commandCur);
	ICommand_Ptr command_cur_ptr = queue.process(com_ptr, e);
	bool flagCast;
	if (auto comCur_ptr = dynamic_cast<CommandRepeat*>(command_cur_ptr.get()))
		flagCast = true;
	else
		flagCast = false;

	ICommand_Ptr command_cur_ptrRepeat = queue.process(command_cur_ptr, e);
	bool flagCast2;
	if (auto comCur_ptr = dynamic_cast<CommandRepeatTwo*>(command_cur_ptrRepeat.get()))
		flagCast2 = true;
	else
		flagCast2 = false;

	ICommand_Ptr command_cur_ptrRepeatTwo = queue.process(command_cur_ptrRepeat, e);
	bool flagCast3;
	if (auto comCur_ptr = dynamic_cast<CommandLogger*>(command_cur_ptrRepeatTwo.get()))
		flagCast3 = true;
	else
		flagCast3 = false;

	ASSERT_TRUE(flagCast && flagCast2 && flagCast3);
}