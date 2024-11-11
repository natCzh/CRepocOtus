#ifndef _SHOTABLE_ADAPTER_H_
#define _SHOTABLE_ADAPTER_H_

#include <vector>

#include "Common/objectAble/IShotable.h"
#include "IoC/IoCGlobal.h"
#include "Common/UObject.h"

class ShotableAdapter : public IShotable
{
public:

	ShotableAdapter(UObject_Ptr obj_)
		: obj(obj_)
	{}

	boost::any getNumberShot() override
	{
		return ioc.Resolve<int>("IShotable.NumberShot", obj);
	}

	void setShotAct() override
	{
		int newValueAny = boost::any_cast<int>(1);
		ioc.Resolve<ICommand_Ptr>("IShotable.ShotAct.Set", obj, newValueAny);
	}

	void setNumberShot(boost::any& newValue) override
	{
		int newValueAny = boost::any_cast<int>(newValue);
		ioc.Resolve<ICommand_Ptr>("IShotable.NumberShot.Set", obj, newValueAny);
	}

protected:
	UObject_Ptr									obj;
};

#endif /* _SHOTABLE_ADAPTER_H_ */
