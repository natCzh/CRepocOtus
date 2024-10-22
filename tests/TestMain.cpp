
# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include "src/IoC.h"
#include "src/Exception/IoCException.h"

TEST(TestCommandExecute, test_register)
{
	class MoveCommand: public ICommand
	{
	public:
		int Execute()
		{
			return 0;
		}

		std::string GetType()
		{
			return "MoveCommand";
		}
	 };

	MoveCommand curMove;
	ICommand_Ptr ICurrentCommand = std::make_shared<MoveCommand>(curMove);
	inputParamsIocRegister params;
	params.strCommand = "MoveCommand";
	params.command = ICurrentCommand;

	IoC ioc;
	std::string key = "IoC.Register";
	
	EXPECT_THROW(ioc.Resolve<ICommand>(key, (void*)(&params)), IoCException);
}