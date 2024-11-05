#ifndef _REGISTER_DEPENDENCY_COMMAND_H_
#define _REGISTER_DEPENDENCY_COMMAND_H_

#include <functional>

#include "Command/ICommand.h"
#include "scopes/DependencyResolve.h"

template<typename... Args>
struct tuple;

template<typename T, typename... Args>
class RegisterDependencyCommand: public ICommand
{
	RegisterDependencyCommand(std::shared_ptr<Scopes::DependencyResolve> depency_, std::string key_, std::function<T(Args... arg)> fun_)
		: depency(depency_)
		, key(key_)
		, fun(fun_)
	{}

	void Execute()
	{
		auto currentScope = depency->GetCurrentScope();
		currentScope->Add(key, boost::any_cast(fun));
	}

protected:
	std::shared_ptr<Scopes::DependencyResolve>														depency;
	std::string																						key;
	std::function<T(Args... arg)>																	fun;
};

#endif /* _REGISTER_DEPENDENCY_COMMAND_H_ */