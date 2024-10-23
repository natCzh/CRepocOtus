#ifndef _I_O_C_H_
#define _I_O_C_H_

#include <cstring>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "src/Command/ICommand.h"

struct inputParamsIocRegister
{
	std::string							strCommand;
	ICommand_Ptr						command;
};

namespace Scopes
{ class IDependencyResolve; }


// уже разрешенные команды в IoC
// IoC.Register, Scopes.New, Scopes.Current, Scopes.Delete

class IoC
{
public:

	template<typename T>
	std::shared_ptr<T> Resolve(std::string key, void *args)
	{
		if (strcmp(key.c_str(), "IoC.Register") == 0)
		{
			Register(args);
			return std::shared_ptr<CommandEmpty>(new CommandEmpty);
		}
		else if (strcmp(key.c_str(), "Scopes.New") == 0 || strcmp(key.c_str(), "Scopes.Current") == 0 || strcmp(key.c_str(), "Scopes.Delete") == 0)
		{
			ScopesProcessing(key, args);
			return std::shared_ptr<CommandEmpty>(new CommandEmpty);
		}
		else
			return ResolveCommand(key, args);
	}

protected:

	ICommand_Ptr ResolveCommand(const std::string &key, void *args);

	void Register(void *args);

	void CreateScope(size_t idScope);
	void SetCurrentScope(size_t idScope);
	void DeleteScope(size_t idScope);

	void ScopesProcessing(std::string key, void *args);

	std::unordered_map<int, std::shared_ptr<Scopes::IDependencyResolve> >		scopes;
	std::shared_ptr<Scopes::IDependencyResolve>									currentScope;

	std::mutex																	mutex;
};

#endif /* _I_O_C_H_ */