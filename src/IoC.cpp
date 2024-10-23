#include <iostream>

#include "IoC.h"
#include "src/scopes/DependencyResolve.h"
#include "src/Exception/IoCException.h"

ICommand_Ptr IoC::ResolveCommand(const std::string &key, void *args)
{
	UObject *obj = static_cast<UObject *>(args);
	return currentScope->Resolve(key, obj);
}

void IoC::Register(void *args)
{
	inputParamsIocRegister curParams = *(static_cast<inputParamsIocRegister *>(args));

	if (curParams.strCommand.empty() || !curParams.command)
		throw IoCException("IocRegister error, parameters isn't inputParamsIocRegister type");
	if (!currentScope)
		throw IoCException("IocRegister error, current scope not exist");
	std::lock_guard<std::mutex> lock(mutex);
	currentScope->AddCommand(curParams.strCommand, curParams.command);
}

void IoC::CreateScope(size_t idScope)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (scopes.empty() || scopes.find(idScope) == scopes.end())
		scopes[idScope] = std::make_shared<Scopes::DependencyResolve>();
	else 
		throw IoCException("IocRegister error, current scope is exist");
}

void IoC::ScopesProcessing(std::string key, void *args)
{
	if (strcmp(key.c_str(), "Scopes.New") == 0)
		CreateScope(*static_cast<size_t *>(args));
	else if (strcmp(key.c_str(), "Scopes.Current") == 0)
		SetCurrentScope(*static_cast<size_t *>(args));
	else if (strcmp(key.c_str(), "Scopes.Delete") == 0)
		DeleteScope(*static_cast<size_t *>(args));
}

void IoC::SetCurrentScope(size_t idScope)
{
	std::lock_guard<std::mutex> lock(mutex);
	auto iterScope = scopes.find(idScope);
	if (iterScope != scopes.end())
		currentScope = iterScope->second;
	else 
		throw IoCException("IocRegister error, set current scope isn't exist");
}

void IoC::DeleteScope(size_t idScope)
{
	std::lock_guard<std::mutex> lock(mutex);
	auto iterScope = scopes.find(idScope);
	if (iterScope != scopes.end())
	{
		// удаляем
		if (currentScope == iterScope->second)
			currentScope.reset();
		scopes.erase(iterScope);
	}
	else
		throw IoCException("IocRegister error, deletable scope isn't exist");
}