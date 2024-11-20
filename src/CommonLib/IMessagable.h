#ifndef _I_MESSAGABLE_H_
#define _I_MESSAGABLE_H_

#include <string>
#include <map>
#include <boost/any.hpp>

class IMessagable
{
public:

	virtual ~IMessagable() {}

	virtual unsigned int getIdGame() = 0;
	virtual unsigned int getIdObject() = 0;
	virtual std::string getTypeCommand() = 0;
	virtual std::map<std::string, boost::any> getProperties() = 0;
};

using IMessagable_Ptr = std::shared_ptr<IMessagable>;

#endif /* _I_MESSAGABLE_H_ */
