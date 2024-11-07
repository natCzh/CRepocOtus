#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <functional>
#include <thread>

#include "IoC/IoC.h"
#include "src/Exception/ScopesException.h"
#include "src/Exception/IoCException.h"
#include "src/Command/ICommand.h"

TEST(TestIoCScopes, getNewEmptyScopeAndSet)
{
	IoC ioc;
	std::shared_ptr<Scopes::Scope> newScope = ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Empty", 1);
	EXPECT_TRUE(newScope.get() != nullptr);
	// проверка на разрешенные зависимости
	EXPECT_THROW(newScope->GetValueOrDefault("A"), IoCException);
	EXPECT_THROW(newScope->GetValueOrDefault("Scopes.Create.Root"), IoCException);

	// повторное создание скоупа с ид
	EXPECT_THROW(ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Root", 1), ScopesException);

	// создание рутового скоупа
	std::shared_ptr<Scopes::Scope> newScopeRoot2 = ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Root", 2);
	EXPECT_THROW(newScopeRoot2->GetValueOrDefault("A"), IoCException);
	EXPECT_NO_THROW(newScopeRoot2->GetValueOrDefault("Scopes.Create.Root"), IoCException);
}

int reg1(int x)
{
	return x;
}

TEST(TestIoCScopes, getCurrentScope)
{
	IoC ioc;
	std::shared_ptr<Scopes::Scope> currentScope = ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Current");
	// проверка, что в текущем скоупе есть зависимости по инициализации
	EXPECT_THROW(currentScope->GetValueOrDefault("A"), IoCException);
	EXPECT_NO_THROW(currentScope->GetValueOrDefault("Scopes.Create.Root"), IoCException);
	int x = 0;
	EXPECT_THROW(ioc.Resolve<int>("A", x), IoCException);
	EXPECT_NO_THROW(std::shared_ptr<Scopes::Scope> newScope = ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Root", 3), ScopesException);

	// запишем зависимость и проверим, что она есть в скоупе
	std::function<int(int)> func = &reg1;
	// регистрация
	ioc.Resolve<ICommand_Ptr, int, std::string, std::function<int(int)> >("IoC.Register", "A", func, x)->Execute();
	EXPECT_NO_THROW(int d = ioc.Resolve<int>("A", x), IoCException);

	// создадим пустой скоуп и сделаем его текущим и проверим все тоже самое
	std::shared_ptr<Scopes::Scope> newScope = ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Empty", 4);
	ioc.Resolve<void>("Scopes.Current.Set", newScope);
	EXPECT_THROW(ioc.Resolve<int>("A", x), IoCException);
	EXPECT_THROW(ioc.Resolve<std::shared_ptr<Scopes::Scope> >("Scopes.Create.Root", 4), IoCException);
}
