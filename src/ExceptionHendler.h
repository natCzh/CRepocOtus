#ifndef _EXCEPTION_HENDLER_H_
#define _EXCEPTION_HENDLER_H_

#include "StoreDict.h"

class ExceptionHendler
{
public:

	ICommand_Ptr Handle(ICommand_Ptr c, const std::exception &e)
	{
		std::string typeC = c->GetType();
		std::string typeE = e.what();

		return (store.GetValueOrDefault(typeC, typeE))(c, e);
	}

	void RegisterHandler(const std::string &typeC, const std::string &typeE, FunctHendler commandData)
	{
		store.AddItems(typeC, typeE, commandData);
	}

private:

	StoreDict											store;
};

#endif _EXCEPTION_HENDLER_H_
