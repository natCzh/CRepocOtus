#ifndef _CLASS_FUNCTION_MOVE_H_
#define _CLASS_FUNCTION_MOVE_H_

#include <cmath>
#include <memory>

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"
#include "CommandMove.h"
#include "../../CommonLib/objectAble/IMovable.h"
#include "MovableAdapter.h"
#include "IoC/IoC.h"
#include "IMovableLocationSetClass.h"

extern IoC* ioc;
class ClassFunctionMove
{
public:

	ClassFunctionMove() {}
	virtual ~ClassFunctionMove() {}

    std::vector<int> IMovableLocationFunc(UObject_Ptr obj)
	{
		std::vector<int> locationCur;
		locationCur.push_back(boost::any_cast<int>(obj->getProperty("position_x")));
		locationCur.push_back(boost::any_cast<int>(obj->getProperty("position_y")));

		return locationCur;
	}

    ICommand_Ptr IMovableLocationSetFunc(UObject_Ptr obj, std::vector<int> value)
	{
        return ICommand_Ptr(new IMovableLocationSetClass(obj, value));
	}

    std::vector<int> IMovableVelocityFunc(UObject_Ptr obj)
	{
		std::vector<int> velCur;

		int d = boost::any_cast<int>(obj->getProperty("direction"));
		int n = boost::any_cast<int>(obj->getProperty("directionNumber"));
        int vel = boost::any_cast<int>(obj->getProperty("velocity"));

		std::vector<int> locationCur;
		int angle = d * 360 / n;
		locationCur.push_back(vel * std::cos(angle / 180 * M_PI));
		locationCur.push_back(vel * std::sin(angle / 180 * M_PI));

		return locationCur;
	}

    std::shared_ptr<IMovable> AdaptersIMovableFunc(UObject_Ptr obj)
	{
		return std::shared_ptr<IMovable>(new MovableAdapter(obj));
	}

    ICommand_Ptr CommandMoveFunc(UObject_Ptr obj)
	{
		return ICommand_Ptr(new CommandMove(ioc->Resolve<std::shared_ptr<IMovable> >("Adapters.IMovable", obj)));
	}
};

#endif /* _CLASS_FUNCTION_MOVE_H_ */
