 #ifndef _MOVE_COMMAND_H_
#define _MOVE_COMMAND_H_

#include "Command/ICommand.h"
#include "Common/UObject.h"
#include "Exception/IoCException.h"

class MoveCommand: ICommand
{
public:
	MoveCommand(const std::shared_ptr<UObject> &obj)
		: o(obj)
	{}

	// return 0 - ok,
	 // 1 - error
	void Execute()
	{
		boost::any posCur_any, velCur_any;
		int errorCode = o->getProperty("position_x", posCur_any);
		if (errorCode)
			throw IoCException("UObject - position_x isn't exist");
		errorCode = o->getProperty("velocity_x", velCur_any);
		if (errorCode)
			throw IoCException("UObject - velocity_x isn't exist");
		int pos1 = boost::any_cast<int>(posCur_any) + boost::any_cast<int>(velCur_any);
		o->setProperty("position_x", pos1);

		errorCode = o->getProperty("position_y", posCur_any);
		if (errorCode)
			throw IoCException("UObject - position_y isn't exist");
		errorCode = o->getProperty("velocity_y", velCur_any);
		if (errorCode)
			throw IoCException("UObject - velocity_y isn't exist");
		pos1 = boost::any_cast<int>(posCur_any) + boost::any_cast<int>(velCur_any);
		o->setProperty("position_y", pos1);
	}

	std::string GetType()
	{
		return "MoveCommand";
	}

private:
	std::shared_ptr<UObject> o;
};

#endif /* _MOVE_COMMAND_H_ */
