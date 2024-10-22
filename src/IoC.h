#ifndef _I_O_C_H_
#define _I_O_C_H_

#include <string>
#include <iostream>
#include <memory>
#include <mutex>

#include "src/scopes/DependencyResolve.h"
#include "src/Exception/IoCException.h"
#include "src/scopes/ScopesProcessing.h"

struct inputParamsIocRegister
{
	std::string							strCommand;
	ICommand_Ptr						command;
};

class IoC
{
public:

	template<typename T>
	std::shared_ptr<T> Resolve(std::string key, void *args)
	{
		if (strcmp(key.c_str(), "IoC.Register") == 0)
		{
			Register(args);
			return nullptr;
		}
		/*else if (strcmp(key.c_str(), "Scopes.New") == 0 || strcmp(key.c_str(), "Scopes.Current") == 0 || strcmp(key.c_str(), "Scopes.Delete") == 0)
			ScopesProcessing::*/
		else
			return ResolveCommand(key, args);

		// else if ()
	}

protected:

	ICommand_Ptr ResolveCommand(const std::string &key, void *args);

	void Register(void *args);

	void CreateScope();

	std::unordered_map<int, Scopes::DependencyResolve>							scopes;
	std::shared_ptr<Scopes::DependencyResolve>									currentScope;

	std::mutex																	mutex;
};

#endif /* _I_O_C_H_ */