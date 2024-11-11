#ifndef _CLASS_FUNCTION_ROTATE_H_
#define _CLASS_FUNCTION_ROTATE_H_

#include <cmath>

#include "Command/ICommand.h"
#include "Common/UObject.h"
#include "Exception/UobjectException.h"
#include "inputPlugins/RotateCommandPlugin/RotableAdapter.h"
#include "inputPlugins/RotateCommandPlugin/CommandRotate.h"

class ClassFunctionRotate
{
public:

	ClassFunctionRotate() {}
	virtual ~ClassFunctionRotate() {}

	static int IRotableDirectionFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("direction"));
		return d;
	}

	static void IRotableDirectionSetFunc(UObject_Ptr obj, boost::any value)
	{
		obj->setProperty("direction", value);
	}

	static int IRotableDirectionAngularFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("directionAngular")); // дб 1 или -1 против часовой, по часовой
		return d;
	}

	static int IRotableDirectionNumberFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("directionNumber"));
		return d;
	}

	static std::shared_ptr<IRotable> AdaptersIRotableFunc(UObject_Ptr obj)
	{
		return std::shared_ptr<IRotable>(new RotableAdapter(obj));
	}

	static ICommand_Ptr CommandRotateFunc(UObject_Ptr obj)
	{
		return ICommand_Ptr(new CommandRotate(ioc.Resolve<std::shared_ptr<IRotable> >("Adapters.IRotable", obj)));
	}
};

#endif /* _CLASS_FUNCTION_ROTATE_H_ */
