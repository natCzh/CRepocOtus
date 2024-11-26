#ifndef _I_MESSAGABLE_START_GAME_H_
#define _I_MESSAGABLE_START_GAME_H_

#include <string>
#include <map>
#include <boost/any.hpp>
#include <vector>

class IMessagableStartGame
{
public:

    virtual ~IMessagableStartGame() {}

    virtual std::vector<unsigned long long> getIdObjects() = 0;
    virtual std::vector<unsigned long long> getTypeObjs() = 0;
	virtual std::map<std::string, boost::any> getProperties() = 0;
};

using IMessagableStartGame_Ptr = std::shared_ptr<IMessagableStartGame>;

#endif /* _I_MESSAGABLE_START_GAME_H_ */
