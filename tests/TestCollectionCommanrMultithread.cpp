#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "src/CommandCollection.h"



class MoveCommandMock : public ICommand
{
public:
	MoveCommandMock() {}

	virtual ~MoveCommandMock() {}

	MOCK_METHOD(std::string, GetType, (), (override));
	MOCK_METHOD(void, Execute, (), (override));
};
class Com : public ICommand
{
public:
	Com() {}

	virtual ~Com() {}

	void Execute()
	{
		int sdf = 0;
	}

	std::string GetType()
	{
		return "1";
	}

};

/*class threada*
{
public:/
	void start()
	{

	}



};*/


// проверка, что после команды старт поток запущен
TEST(TestCollectionCommonMultithread, testStart)
{

	Com m;
	MoveCommandMock moveCommandMock;
	//std::shared_ptr<MoveCommandMock> cmd_ptr_ = std::make_shared<MoveCommandMock>();
	std::shared_ptr<ICommand> cmd_ptr_ = std::make_shared<Com>(m);
	//EXPECT_CALL(*cmd_ptr_, Execute()).Times(1);

	CommandCollection commandColection;
			commandColection.add(cmd_ptr_);
	commandColection.startLoop();

	//thread_local

	std::this_thread::sleep_for(std::chrono::seconds(5));
	commandColection.stop();


	//
	/*EXPECT_CALL(*cmd_ptr_, Execute()).Times(1);

		CommandCollection commandColection;
	commandColection.add(cmd_ptr_);
	commandColection.startLoop();
	commandColection.stop();*/

	//testing::Mock::VerifyAndClearExpectations((cmd_ptr_)->ge );	
}
