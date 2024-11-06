# include "gtest/gtest.h"
# include "gmock/gmock.h"
#include "IoC/IoCNew.h"
#include "src/Exception/IoCException.h"
#include "src/Command/MoveCommand.h"
#include "src/Command/ICommand.h"

#include <typeinfo>

#include <functional>

/*class MoveCommandMock : public ICommand
{
public:
	MoveCommandMock() {}
	virtual ~MoveCommandMock() {}
	MoveCommandMock(const MoveCommandMock &other)
	{}

	MOCK_METHOD0(GetType, std::string());
	MOCK_METHOD0(Execute, void());
};*/
/*
#include <functional> 
	class A
	{
	public:

					// вызов стратегии
		template<typename T, typename ... ARG>
		T resolve(ARG ... arg)
		{



			std::cout << "resolve 1 " << std::typeid(T).name() << std::endl;
		}




			// вызов стратегии
		template<typename T>
		T resolve(std::string &type)
		{
			int e = 0;
//			auto cx = std::typeid(e);
			//std::cout << "resolve 1 " << std::typeid(T).name() << std::endl;
			return (T)e;
		}

		// регистрация
		template<typename T>
		T resolve(std::string &type, std::string &structType, std::function < T(void)>)
		{
			std::cout << "resolve 2 " << std::typeid(T).name() << ", " << structType << std::endl;
		}
	};


TEST(TestIoCCommand, registerCommand1)
{
	A a;
	std::string str1 = "1int";
	int res = a.resolve<int>(str1);

}*/


/*TEST(TestIoCCommand, registerCommand)
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
	ICommand_Ptr params_ptr = pa_ptr;
	params.strCommand = "MoveCommandMock";
	params.command = params_ptr;
	ioc.Resolve<ICommand>("IoC.Register", static_cast<void*>(&params));

	EXPECT_CALL(moveCommand, Execute()).WillOnce(testing::Return());

	ICommand_Ptr cur = ioc.Resolve<ICommand>("MoveCommandMock", static_cast<void*>(&params));
	cur->Execute();
	



	// ---------------------------------



	//ioc.Resolve<ICommand>("MoveCommandMock", static_cast<void*>(&params)).Execute(); //тут пар-ов нет
	//ioc.Resolve<ICommand>("IoC.Register", static_cast<void*>(&params)); // "завимисость", std::function void()





}*/

#include "Command/CommandEmpty.h"

TEST(TestIoCCommand, commonIoC)
{
	IoC ioc;

	CommandEmpty emptyCmd;
	int x = 1;
	// [&]() {return x;  }
	//ioc.Resolve<ICommand_Ptr, std::string, std::function<void()> >("IoC.Register", "A", [&]() {return x; } );
	auto del = ioc.Resolve<ICommand_Ptr>("IoC.Register", "A", [&]() {return emptyCmd; });
	del->Execute();
	int sdfsd = 0;

}