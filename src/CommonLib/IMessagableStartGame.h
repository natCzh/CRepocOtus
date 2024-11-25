#ifndef _I_MESSAGABLE_START_GAME_H_
#define _I_MESSAGABLE_START_GAME_H_

#include <string>
#include <map>
#include <boost/any.hpp>

class IMessagableStartGame
{
public:

    virtual ~IMessagableStartGame() {}

    virtual unsigned long long getIdObject() = 0;
    virtual unsigned long long getTypeObj() = 0;
	virtual std::map<std::string, boost::any> getProperties() = 0;
};

using IMessagableStartGame_Ptr = std::shared_ptr<IMessagableStartGame>;

#endif /* _I_MESSAGABLE_START_GAME_H_ */
