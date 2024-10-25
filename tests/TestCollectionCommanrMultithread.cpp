#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CollectionCommand.h"
#include "Command/CommandCollection.h"

class MoveCommandMock : public ICommand
{
public:
	MoveCommandMock() {}

	virtual ~MoveCommandMock() {}

	MOCK_METHOD(std::string, GetType, (), (override));
	MOCK_METHOD(void, Execute, (), (override));
};

// проверка, что после команды старт поток запущен
TEST(TestCollectionCommonMultithread, testStart)
{
	std::shared_ptr<MoveCommandMock> cmd_ptr = std::make_shared<MoveCommandMock>();
	std::shared_ptr<ICommand> cmd_ptr_ = cmd_ptr;
	EXPECT_CALL(*cmd_ptr, Execute()).Times(1);

	CommandCollection commandColection;
	commandColection.add(cmd_ptr_);
	commandColection.startLoop();
	std::this_thread::sleep_for(std::chrono::microseconds());
	commandColection.stop();
}

// проверка hardStop
TEST(TestCollectionCommonMultithread, testHardStop)
{
	std::shared_ptr<MoveCommandMock> cmd_ptr = std::make_shared<MoveCommandMock>();
	std::shared_ptr<ICommand> cmd_ptr_ = cmd_ptr;
	EXPECT_CALL(*cmd_ptr, Execute()).Times(2);

	std::shared_ptr<CommandCollection> commandColection(new CommandCollection());
	std::shared_ptr<ICommand> cmd_ptr_hs = std::make_shared<CommandCollectionHardStop>(commandColection);
	commandColection->add(cmd_ptr_);
	commandColection->add(cmd_ptr_);
	commandColection->add(cmd_ptr_hs);
	commandColection->add(cmd_ptr_);
	commandColection->startLoop();
	std::this_thread::sleep_for(std::chrono::microseconds(5));
	commandColection->stop();
}

// проверка softStop
TEST(TestCollectionCommonMultithread, testSoftStop)
{
	std::shared_ptr<MoveCommandMock> cmd_ptr = std::make_shared<MoveCommandMock>();
	std::shared_ptr<ICommand> cmd_ptr_ = cmd_ptr;
	EXPECT_CALL(*cmd_ptr, Execute()).Times(3);

	std::shared_ptr<CommandCollection> commandColection(new CommandCollection());
	std::shared_ptr<ICommand> cmd_ptr_hs = std::make_shared<CommandCollectionSoftStop>(commandColection);
	commandColection->add(cmd_ptr_);
	commandColection->add(cmd_ptr_);
	commandColection->add(cmd_ptr_hs);
	commandColection->add(cmd_ptr_);
	commandColection->startLoop();
	std::this_thread::sleep_for(std::chrono::microseconds(5));
	commandColection->stop();
}
