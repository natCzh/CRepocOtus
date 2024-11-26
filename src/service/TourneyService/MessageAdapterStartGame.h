#ifndef _MESSAGE_ADAPTER_START_GAME_H_
#define _MESSAGE_ADAPTER_START_GAME_H_

#include <memory>

#include "CommonLib/IMessagableStartGame.h"
#include "CommonLib/UObject.h"

class MessageAdapterStartGame : public IMessagableStartGame
{
public:

	// TODO переписать через IoC
    MessageAdapterStartGame(std::shared_ptr<UObject> message_)
		: message(message_)
	{}

    virtual ~MessageAdapterStartGame() {};

    std::vector<unsigned long long> getIdObjects() override
	{
        boost::any val = message->getProperty("idObjsNewGame");
        return boost::any_cast<std::vector<unsigned long long> >(val);
	}

    std::vector<unsigned long long> getTypeObjs() override
	{
        boost::any val = message->getProperty("typeObjs");
        return boost::any_cast<std::vector<unsigned long long> >(val);
	}
	
    std::map<std::string, boost::any> getProperties() override
	{
        boost::any val = message->getProperty("args");
		return boost::any_cast<std::map<std::string, boost::any> >(val);
	}

private:
	std::shared_ptr<UObject>									message;
};

#endif /* _MESSAGE_ADAPTER_START_GAME_H_ */
