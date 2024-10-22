#include "IoC.h"

void IoC::Register(void *args)
{
	inputParamsIocRegister curParams = *(static_cast<inputParamsIocRegister *>(args));

	if (curParams.strCommand.empty() || !curParams.command)
		throw IoCException("IocRegister error, parameters isn't inputParamsIocRegister type");
	if(!currentScope)
		throw IoCException("IocRegister error, current scope not exist");
	currentScope->AddCommand(curParams.strCommand, curParams.command);
}

ICommand_Ptr IoC::ResolveCommand(const std::string &key, void *args)
{
	UObject *obj = static_cast<UObject *>(args);
	return currentScope->Resolve(key, obj);
}

void IoC::CreateScope()
{
	std::lock_guard<std::mutex> lock(mutex);
}

template<typename T>
std::shared_ptr<T> Resolve(std::string key, void *args)
{
	if (strcmp(key.c_str(), "IoC.Register") == 0)
	{
		Register(args);
		return nullptr;
	}
	else if (strcmp(key.c_str(), "Scopes.New") == 0 || strcmp(key.c_str(), "Scopes.Current") == 0 || strcmp(key.c_str(), "Scopes.Delete") == 0)
		int v = 0;
	else
		return ResolveCommand(key, args);

	// else if ()
}