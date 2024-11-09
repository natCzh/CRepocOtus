#ifndef _COMMAND_MOVE_H_
#define _COMMAND_MOVE_H_

#include "Command/ICommand.h"
#include "Common/objectAble/IMovable.h"

class CommandMove: public ICommand
{
public:
	CommandMove(std::shared_ptr<IMovable> obj_)
		: obj(obj_) 
	{}
	
	void Execute() override
	{
		std::vector<int> loc = boost::any_cast<std::vector<int> >(obj->getLocation());
		std::vector<int> vec = boost::any_cast<std::vector<int>>(obj->getVelocity());
		std::vector<int> newLoc = { loc[0] + vec[0], loc[1] + vec[1] };

		boost::any newValue = newLoc;
		obj->setLocation(newValue);
	}

	std::string GetType() override
	{
		return "CommandMove";
	}
	
protected:

	std::shared_ptr<IMovable>			obj;
};

#endif /* _COMMAND_MOVE_H_ */
