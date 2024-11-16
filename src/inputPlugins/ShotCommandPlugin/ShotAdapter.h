#ifndef _SHOTABLE_ADAPTER_H_
#define _SHOTABLE_ADAPTER_H_

#include <vector>
#include <memory>

#include "../../CommonLib/objectAble/IShotable.h"
#include "../../CommonLib/UObject.h"
#include "IoC/IoC.h"

extern IoC* ioc;
class ShotableAdapter : public IShotable
{
public:

	ShotableAdapter(UObject_Ptr obj_)
		: obj(obj_)
	{}

	boost::any getNumberShot() override
	{
        return ioc->Resolve<int>("IShotable.NumberShot", obj);
	}

	void setShotAct() override
	{
		int newValueAny = boost::any_cast<int>(1);
        ioc->Resolve<ICommand_Ptr>("IShotable.ShotAct.Set", obj, newValueAny)->Execute();
	}

	void setNumberShot(boost::any& newValue) override
	{
		int newValueAny = boost::any_cast<int>(newValue);
        ioc->Resolve<ICommand_Ptr>("IShotable.NumberShot.Set", obj, newValueAny)->Execute();
	}

protected:
	UObject_Ptr									obj;
};

#endif /* _SHOTABLE_ADAPTER_H_ */
