#ifndef _STORE_DICT_H_
#define _STORE_DICT_H_

#include <map>
#include <functional>
#include <string>
#include <memory>

#include "Command/ICommand.h"
#include "HandlerFactory.h"

using FunctHendler = std::function<ICommand_Ptr(ICommand_Ptr, const std::exception &)>;

class StoreDict
{
public:
	StoreDict() {}

	FunctHendler GetValueOrDefault(std::string typeC, std::string typeE)
	{
		auto iterF = store.find(typeC);
		if (iterF != store.end())
			return GetICommandFromError(iterF->second, typeE);
		else
			return GetICommandFromError(defaultStore, typeE);
	}

	void AddItems(std::string typeC, std::string typeE, const FunctHendler &command)
	{
		// TODO тут еще неплохо проверять есть ли такой ключ
		store[typeC][typeE] = command;
	}


private:
	std::map<std::string, std::map<std::string, FunctHendler > >			store;
	std::map<std::string, FunctHendler >									defaultStore;

	//HandlerErrorDefault														defaultCommand;

	FunctHendler GetICommandFromError(const std::map<std::string, FunctHendler > & curStore, const std::string& strTypeE)
	{
		auto iterC = curStore.find(strTypeE);
		if (iterC != curStore.end())
			return iterC->second;
		//else
		//	return defaultCommand.process(ICommand_Ptr, const std::exception &); // TODO дописать !!!!!!!
	}
};

#endif _STORE_DICT_H_
