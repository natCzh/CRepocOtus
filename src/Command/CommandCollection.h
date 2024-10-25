#ifndef _COMMAND_COLLECTION_H_
#define _COMMAND_COLLECTION_H_

#include "ICommand.h"
#include "CommandCollection.h"

class CommandCollectionHardStop : public ICommand
{
public:

	CommandCollectionHardStop(std::shared_ptr<CommandCollection> collection_)
		: collection(collection_)
	{}

	virtual ~CommandCollectionHardStop()
	{}
	
	void Execute()
	{
		collection->stop();
	}

	std::string GetType()
	{
		return "CommandCollectionHardStop";
	}

protected:
	std::shared_ptr<CommandCollection>						collection;
};

class CommandCollectionSoftStop : public ICommand
{
public:

	CommandCollectionSoftStop(std::shared_ptr<CommandCollection> collection_)
		: collection(collection_)
	{}
	
	void Execute()
	{
		collection->softStop();
	}

	std::string GetType()
	{
		return "CommandCollectionSoftStop";
	}

protected:
	std::shared_ptr<CommandCollection>						collection;
};

#endif /* _COMMAND_COLLECTION_H_ */