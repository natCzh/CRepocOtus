#ifndef _BOOT_STRAP_HANDLER_H_
#define _BOOT_STRAP_HANDLER_H_

#include "HandlerFactory.h"
#include "ExceptionHendler.h"
#include "ICommand.h"

class BootStrapHandler
{
public:

	BootStrapHandler() {}

	void LoadSetting(ExceptionHendler &exc, const QueueCommand &q)
	{
		handlerErrorDefault = std::make_shared<HandlerErrorDefault>();
		handlerLogQueue = std::make_shared<HandlerLogQueue>(q);

		/////////////////////////////////////////////////
		// exc.RegisterHandler("CommandErrorDefault", "Unknown exception", &(handlerErrorDefault->process));
		auto funcPtr = std::bind(&HandlerLogQueue::process, handlerLogQueue.get(), std::placeholders::_1, std::placeholders::_2);
		exc.RegisterHandler("CommandAddQueueEnd", "Unknown exception", funcPtr);
	}

	// hendler
	std::shared_ptr<HandlerErrorDefault>				handlerErrorDefault;
	std::shared_ptr<HandlerLogQueue>					handlerLogQueue;
};

// command 
// CommandErrorDefault
// CommandAddQueueEnd

#endif _BOOT_STRAP_HANDLER_H_