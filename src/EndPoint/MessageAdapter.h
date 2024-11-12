#ifndef _MESSAGE_ADAPTER_H_
#define _MESSAGE_ADAPTER_H_

#include <memory>

#include "EndPoint/IMessagable.h"
#include "EndPoint/Message.h"

class MessageAdapter : public IMessagable
{
public:

	// TODO ���������� ����� IoC
	MessageAdapter(std::shared_ptr<UObject> message_)
		: message(message_)
	{}

	virtual ~MessageAdapter() {};

	unsigned int getIdGame()
	{
		boost::any val = message->getProperty("id.Game");
		return boost::any_cast<unsigned int>(val);
	}

	unsigned int getIdObject()
	{
		boost::any val;
		message->getProperty("id.Object", val);
		return boost::any_cast<unsigned int>(val);
	}

	std::string getTypeCommand()
	{
		boost::any val;
		message->getProperty("TypeCommand", val);
		return boost::any_cast<std::string>(val);
	}
	
	std::map<std::string, boost::any> getProperties()
	{
		boost::any val;
		message->getProperty("TypeCommand", val);
		return boost::any_cast<std::map<std::string, boost::any> >(val);
	}

private:
	std::shared_ptr<UObject>									message;
};

#endif /* _MESSAGE_ADAPTER_H_ */
