# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include "src/IoC.h"
#include "src/Exception/IoCException.h"
#include "src/Command/MoveCommand.h"
#include "src/Command/ICommand.h"

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


TEST(TestIoCCommand, registerCommand)
{


	IoC ioc;

	// добавляем новый скоуп
	size_t idScope = 0;
	EXPECT_NO_THROW(ioc.Resolve<ICommand>("Scopes.New", static_cast<void*>(&idScope)));
	EXPECT_NO_THROW(ioc.Resolve<ICommand>("Scopes.Current", static_cast<void*>(&idScope)));

	// регистрация команды
	MoveCommandMock moveCommand;
	inputParamsIocRegister params;
	std::shared_ptr<MoveCommandMock> pa_ptr = std::make_shared<MoveCommandMock>(moveCommand);
	ICommand_Ptr params_ptr = std::make_shared<MoveCommandMock>(moveCommand);
	params.strCommand = "MoveCommandMock";
	params.command = params_ptr;
	ioc.Resolve<ICommand>("IoC.Register", static_cast<void*>(&params));

	//EXPECT_CALL(moveCommand, Execute()).WillOnce(testing::Return());

	//ICommand_Ptr cur = ioc.Resolve<ICommand>("MoveCommandMock", static_cast<void*>(&params));
	//cur->Execute();
}