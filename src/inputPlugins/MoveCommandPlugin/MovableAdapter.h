#ifndef _MOVABLE_ADAPTER_H_
#define _MOVABLE_ADAPTER_H_

#include <vector>
#include <memory>

#include "../../CommonLib/objectAble/IMovable.h"
#include "../../CommonLib/UObject.h"
#include "IoC/IoC.h"

extern IoC* ioc;
class MovableAdapter : public IMovable
{
public:

	MovableAdapter(UObject_Ptr obj_)
		: obj(obj_)
	{}

	boost::any getLocation() override
	{
		return ioc->Resolve<std::vector<int> >("IMovable.Location", obj);
	}

	boost::any getVelocity() override
    {
        return ioc->Resolve<std::vector<int> >("IMovable.Velocity", obj);
	}
	void setLocation(boost::any &newValue) override
	{
		std::vector<int> newValueAnyVect = boost::any_cast<std::vector<int>>(newValue);
        ioc->Resolve<ICommand_Ptr>("IMovable.Location.Set", obj, newValueAnyVect)->Execute();
	}

protected:
	UObject_Ptr									obj;
};

#endif /* _MOVABLE_ADAPTER_H_ */
