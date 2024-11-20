#ifndef _MESSAGE_ADAPTER_H_
#define _MESSAGE_ADAPTER_H_

#include <memory>

#include "CommonLib/IMessagable.h"
#include "EndPoint/Message.h"

class MessageAdapter : public IMessagable
{
public:

	// TODO переписать через IoC
	MessageAdapter(std::shared_ptr<UObject> message_)
		: message(message_)
	{}

	virtual ~MessageAdapter() {};

    unsigned int getIdGame() override
	{
		boost::any val = message->getProperty("id.Game");
		return boost::any_cast<unsigned int>(val);
	}

    unsigned int getIdObject() override
	{
        boost::any val = message->getProperty("id.Object");
		return boost::any_cast<unsigned int>(val);
	}

    std::string getTypeCommand() override
	{
        boost::any val = message->getProperty("TypeCommand");
		return boost::any_cast<std::string>(val);
	}
	
    std::map<std::string, boost::any> getProperties() override
	{
        boost::any val = message->getProperty("TypeCommand");
		return boost::any_cast<std::map<std::string, boost::any> >(val);
	}

private:
	std::shared_ptr<UObject>									message;
};

#endif /* _MESSAGE_ADAPTER_H_ */
