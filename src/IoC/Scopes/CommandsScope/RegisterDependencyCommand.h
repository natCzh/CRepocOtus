#ifndef _REGISTER_DEPENDENCY_COMMAND_H_
#define _REGISTER_DEPENDENCY_COMMAND_H_

#include <functional>
#include <string>

#include "../../Command/ICommand.h"
#include "scopes/DependencyResolve.h"

namespace Scopes
{ class DependencyResolve; }

template<typename T, typename... Args>
class RegisterDependencyCommand: public ICommand
{
public:
	virtual ~RegisterDependencyCommand()
	{}

	//template<typename T, typename... Args>
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

template<typename T>
class RegisterDependencyCommand1: public ICommand
{
public:
	virtual ~RegisterDependencyCommand1()
	{}

	//template<typename T>
	RegisterDependencyCommand1(Scopes::DependencyResolve* depency_, std::string key_, std::function<T()> fun_)
		: depency(depency_)
		, key(key_)
		, fun(fun_)
	{}

	void Execute() override
	{
		auto currentScope = depency->GetCurrentScope();
		boost::any v = fun;
		currentScope->Add(key, v);
	}

	std::string GetType() override
	{
		return "RegisterDependencyCommand";
	}

protected:
	Scopes::DependencyResolve*																		depency;
	std::string																						key;
	std::function<T()>																	fun;
};

#endif /* _REGISTER_DEPENDENCY_COMMAND_H_ */