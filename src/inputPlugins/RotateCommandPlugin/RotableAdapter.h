#ifndef _ROTABLE_ADAPTER_H_
#define _ROTABLE_ADAPTER_H_

#include <vector>

#include "Common/objectAble/IRotable.h"
#include "IoC/IoCGlobal.h"
#include "Common/UObject.h"

class RotableAdapter : public IRotable
{
public:

	RotableAdapter(UObject_Ptr obj_)
		: obj(obj_)
	{}

	boost::any getDirecton() override
	{
		return ioc.Resolve<int>("IRotable.Direction", obj);
	}

	void setDirection(boost::any& newValue) override
	{
		int newValueAny = boost::any_cast<int>(newValue);
		ioc.Resolve<ICommand_Ptr>("IRotable.Direction.Set", obj, newValueAny);
	}

	boost::any getDirectonAngular() override
	{
		return ioc.Resolve<int>("IRotable.DirectionAngular", obj);
	}

	boost::any getDirectonNumber() override
	{
		return ioc.Resolve<int>("IRotable.DirectionNumber", obj);
	}

protected:
	UObject_Ptr									obj;
};

#endif /* _ROTABLE_ADAPTER_H_ */
