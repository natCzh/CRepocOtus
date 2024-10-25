#ifndef _START_PROCESSING_COMMAND_COLLECTION_H_
#define _START_PROCESSING_COMMAND_COLLECTION_H_

#include "Command/ICommand.h"
#include "CommandCollection.h"

class StartProcessingCommandCollection : public ICommand
{
public:

	StartProcessingCommandCollection(CommandCollection cmdsCollection_) // TODO переделать чтоб это получалось из Ioc
	{}

	void Execute()
	{
		cmdsCollection.startLoop();
	}

	std::string GetType()
	{
		return "StartProcessingCommandCollection";
	}

private:
	CommandCollection							cmdsCollection;
};

#endif /* _START_PROCESSING_COMMAND_COLLECTION_H_ */
