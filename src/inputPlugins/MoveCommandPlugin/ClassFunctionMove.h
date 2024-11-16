#ifndef _CLASS_FUNCTION_MOVE_H_
#define _CLASS_FUNCTION_MOVE_H_

#include <cmath>
#include <memory>

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../Common/SpaceShip.h" // TODO убрать !!!!!!
#include "../../CommonLib/UobjectException.h"
#include "CommandMove.h"
#include "../../CommonLib/objectAble/IMovable.h"
#include "MovableAdapter.h"
#include "IoC/IoC.h"

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

    int IMovableLocationFunc_Test(UObject_Ptr x)
    {
        /*std::vector<int> locationCur;
        locationCur.push_back(boost::any_cast<int>(obj->getProperty("position_x")));
        locationCur.push_back(boost::any_cast<int>(obj->getProperty("position_y")));

        return locationCur;*/
                std::cout << "plugin test IMovableLocationFunc_Test" << /*x.get() <<*/ std::endl;
        return 0;

    }

    void IMovableLocationSetFunc(UObject_Ptr obj, boost::any value)
	{
		std::vector<int> locationCur = boost::any_cast<std::vector<int> >(value);

		if (locationCur.size() != 2)
			throw UobjectException("Uobject parameter value for set isn't correct");

		boost::any newValue = locationCur[0];
		obj->setProperty("position_x", newValue);
		newValue = locationCur[1];
		obj->setProperty("position_y", newValue);
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
