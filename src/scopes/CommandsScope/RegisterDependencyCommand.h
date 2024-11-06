#ifndef _REGISTER_DEPENDENCY_COMMAND_H_
#define _REGISTER_DEPENDENCY_COMMAND_H_

#include <functional>
#include <string>

#include "Command/ICommand.h"
#include "scopes/DependencyResolve.h"

namespace Scopes
{ class DependencyResolve; }

template<typename T, typename... Args>
class RegisterDependencyCommand: public ICommand
{
public:
	virtual ~RegisterDependencyCommand()
	{}

	template<typename T, typename... Args>
	RegisterDependencyCommand(Scopes::DependencyResolve* depency_, std::string key_, std::function<T(Args... args)> fun_)
		: depency(depency_)
		, key(key_)
		, fun(fun_)
	{}

	void Execute() override
	{
		auto currentScope = depency->GetCurrentScope();
		boost::any v = fun;
		currentScope->Add(key, v);

		auto d = currentScope->GetValueOrDefault("A");
		//std::function<T(Args... args)> df = boost::any_cast<std::function<T(Args... args)> >(d);
		//auto c = df();
		/*ICommand_Ptr c = df();
		c->Execute();*/


		int sdfs = 0;
	}

	std::string GetType() override
	{
		return "RegisterDependencyCommand";
	}

protected:
	Scopes::DependencyResolve*																		depency;
	std::string																						key;
	std::function<T(Args... args)>																	fun;
};

#endif /* _REGISTER_DEPENDENCY_COMMAND_H_ */