#ifndef _CLASS_FUNCTION_SHOT_H_
#define _CLASS_FUNCTION_SHOT_H_

#include <cmath>
#include <memory>

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"
#include "ShotAdapter.h"
#include "CommandShot.h"
#include "../../CommonLib/objectAble/IShotable.h"
#include "IoC/IoC.h"
#include "IShotableSetShotActClass.h"
#include "IShotableSetNumberShotClass.h"

class ClassFunctionShot
{
public:

	ClassFunctionShot() {}
	virtual ~ClassFunctionShot() {}

    int IShotableNumberShotFunc(UObject_Ptr obj)
	{
		int d = boost::any_cast<int>(obj->getProperty("numberShot"));
		return d;
	}

    ICommand_Ptr IShotableShotActSetFunc(UObject_Ptr obj, int value)
	{
        return std::make_shared<IShotableSetShotActClass>(obj, value);
	}

    ICommand_Ptr IShotableNumberShotSetFunc(UObject_Ptr obj, int value)
    {
        return std::make_shared<IShotableSetNumberShotClass>(obj, value);
	}

    std::shared_ptr<IShotable> AdaptersIShotableFunc(UObject_Ptr obj)
	{
        return std::make_shared<ShotableAdapter>(obj);
	}

    ICommand_Ptr CommandShotFunc(UObject_Ptr obj)
	{
        return std::make_shared<CommandShot>(ioc->Resolve<std::shared_ptr<IShotable> >("Adapters.IShotable", obj));
	}
};

#endif /* _CLASS_FUNCTION_SHOT_H_ */
