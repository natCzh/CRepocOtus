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
#include "CommandMovement.h"
#include "CommandMoveLongOperation.h"

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
        return std::make_shared<IMovableLocationSetClass>(obj, value);
	}

    std::vector<int> IMovableVelocityFunc(UObject_Ptr obj)
	{
		std::vector<int> velCur;

		int d = boost::any_cast<int>(obj->getProperty("direction"));
		int n = boost::any_cast<int>(obj->getProperty("directionNumber"));
        int vel = boost::any_cast<int>(obj->getProperty("velocity"));

		std::vector<int> locationCur;
		int angle = d * 360 / n;
        locationCur.push_back(vel * std::cos(angle * M_PI / 180));
        locationCur.push_back(vel * std::sin(angle * M_PI / 180));

		return locationCur;
	}

    std::shared_ptr<IMovable> AdaptersIMovableFunc(UObject_Ptr obj)
	{
        return std::make_shared<MovableAdapter>(obj);
	}

    ICommand_Ptr CommandMoveFunc(UObject_Ptr obj)
	{
        return std::make_shared<CommandMove>(ioc->Resolve<std::shared_ptr<IMovable> >("Adapters.IMovable", obj));
	}

    ICommand_Ptr CommandMovementFunc(size_t idObj)
    {
        return std::make_shared<CommandMovement>(idObj);
    }

    ICommand_Ptr CommandMoveLongOperationFunc(size_t idObj, std::shared_ptr<QueueCommand> qCommand)
    {
        return std::make_shared<CommandMoveLongOperation>(idObj, qCommand);
    }
};

#endif /* _CLASS_FUNCTION_MOVE_H_ */
