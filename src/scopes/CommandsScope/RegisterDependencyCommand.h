#ifndef _REGISTER_DEPENDENCY_COMMAND_H_
#define _REGISTER_DEPENDENCY_COMMAND_H_

#include <functional>
#include <string>

#include "Command/ICommand.h"
#include "scopes/DependencyResolve.h"

namespace Scopes
{ class DependencyResolve; }

template<typename T>
class RegisterDependencyCommand: public ICommand
{
public:
	~RegisterDependencyCommand() {}

	// RegisterDependencyCommand(Scopes::DependencyResolve* depency_, std::string key_) {}
	template<typename T>
	//RegisterDependencyCommand(Scopes::DependencyResolve* depency_, std::string key_, std::function<T()> fun_)
	RegisterDependencyCommand(Scopes::DependencyResolve* depency_, std::string key_, T(*fun_)())
		: depency(depency_)
		, key(key_)
		//, fun(fun_)
	{}

	void Execute() override
	{
		auto currentScope = depency->GetCurrentScope();
		//currentScope->Add(key, boost::any_cast(fun()));
	}

	std::string GetType() override
	{
		return "RegisterDependencyCommand";
	}

protected:
	std::shared_ptr<Scopes::DependencyResolve>														depency;
	std::string																						key;
	//std::function<T()>																						fun;
};

#endif /* _REGISTER_DEPENDENCY_COMMAND_H_ */