#ifndef _I_O_C_H_
#define _I_O_C_H_

#include <cstring>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "src/Command/ICommand.h"
#include "src/Scopes/Scope.h"


//////////////////удалить
#include "EndPoint/MessageAdapter.h"

struct inputParamsIocRegister
{
	std::string							strCommand;
	ICommand_Ptr						command;
};

namespace Scopes
{ class IDependencyResolve; }

class CommandEmpty: public ICommand
{
public:

	virtual ~CommandEmpty() {}

	void Execute() {}

	std::string GetType() { return "CommandEmpty"; }
};

// уже разрешенные команды в IoC
// IoC.Register, Scopes.New, Scopes.Current, Scopes.Delete
// TODO пока класс реализован так ѕ≈–≈ƒ≈Ћј№ !!!!!!!!!
class IoC
{
public:

	template<typename T, typename Z>
	T Resolve(std::string key, Z args)
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
		//template<typename T>
	//std::shared_ptr<T> Resolve(std::string key, void *args)
	template<>
	ICommand_Ptr Resolve(std::string key, boost::any args)
	{
		/*if (strcmp(key.c_str(), "IoC.Register") == 0)
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
			return ResolveCommand(key, args);*/

		return std::shared_ptr<CommandEmpty>(new CommandEmpty);
	}

	template<>
	ICommand_Ptr Resolve (std::string key, std::shared_ptr<MessageAdapter> value)
	{
		// тут ¤то-то произойдет
		return std::shared_ptr<CommandEmpty>(new CommandEmpty);
	}
	




protected:

	ICommand_Ptr ResolveCommand(const std::string &key, void *args);

	void Register(void *args);

	void CreateScope(size_t idScope);
	void SetCurrentScope(size_t idScope);
	void DeleteScope(size_t idScope);

	void ScopesProcessing(std::string key, void *args);

	std::unordered_map<int, std::shared_ptr<Scopes::Scope> >					scopes; // помен¤тьс¤ на boost !!!!!!!!!
	std::shared_ptr<Scopes::Scope>												currentScope;

	std::mutex																	mutex;
};





#endif /* _I_O_C_H_ */