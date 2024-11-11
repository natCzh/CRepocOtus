#ifndef _CLASS_FUNCTION_SHOT_H_
#define _CLASS_FUNCTION_SHOT_H_

#include <cmath>

#include "Command/ICommand.h"
#include "Common/UObject.h"
#include "Exception/UobjectException.h"
#include "inputPlugins/ShotCommandPlugin/ShotAdapter.h"
#include "inputPlugins/ShotCommandPlugin/CommandShot.h"

class ClassFunctionShot
{
public:

	ClassFunctionShot() {}
	virtual ~ClassFunctionShot() {}

	static int IShotableNumberShotFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("numberShot"));
		return d;
	}

	static void IShotableShotActSetFunc(UObject_Ptr obj, boost::any value)
	{
		obj->setProperty("shotAct", value);
	}

	static void IShotableNumberShotSetFunc(UObject_Ptr obj, boost::any value)
	{
		obj->setProperty("numberShot", value);
	}

	static std::shared_ptr<IShotable> AdaptersIShotableFunc(UObject_Ptr obj)
	{
		return std::shared_ptr<IShotable>(new ShotableAdapter(obj));
	}

	static ICommand_Ptr CommandShotFunc(UObject_Ptr obj)
	{
		return ICommand_Ptr(new CommandShot(ioc.Resolve<std::shared_ptr<IShotable> >("Adapters.IShotable", obj)));
	}
};

#endif /* _CLASS_FUNCTION_SHOT_H_ */
