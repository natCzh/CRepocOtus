#ifndef _CLASS_FUNCTION_ROTATE_H_
#define _CLASS_FUNCTION_ROTATE_H_

#include <cmath>
#include <memory>

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"
#include "RotableAdapter.h"
#include "CommandRotate.h"
#include "../../CommonLib/objectAble/IRotable.h"
#include "IoC/IoC.h"
#include "IRotableSetDirectionClass.h"

class ClassFunctionRotate
{
public:

	ClassFunctionRotate() {}
	virtual ~ClassFunctionRotate() {}

    int IRotableDirectionFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("direction"));
		return d;
	}

    ICommand_Ptr IRotableDirectionSetFunc(UObject_Ptr obj, int value)
	{
        return ICommand_Ptr(new IRotableSetDirectionClass(obj, value));
	}

    int IRotableDirectionAngularFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("directionAngular")); // дб 1 или -1 против часовой, по часовой
		return d;
	}

    int IRotableDirectionNumberFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("directionNumber"));
		return d;
	}

    std::shared_ptr<IRotable> AdaptersIRotableFunc(UObject_Ptr obj)
	{
		return std::shared_ptr<IRotable>(new RotableAdapter(obj));
	}

    ICommand_Ptr CommandRotateFunc(UObject_Ptr obj)
	{
        return ICommand_Ptr(new CommandRotate(ioc->Resolve<std::shared_ptr<IRotable> >("Adapters.IRotable", obj)));
	}
};

#endif /* _CLASS_FUNCTION_ROTATE_H_ */
