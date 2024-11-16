#ifndef _I_ROTABLE_SET_DIRECTION_CLASS_H_
#define _I_ROTABLE_SET_DIRECTION_CLASS_H_

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"

class IRotableSetDirectionClass: public ICommand
{
public:

    virtual ~IRotableSetDirectionClass(){}

    IRotableSetDirectionClass(UObject_Ptr obj_, int value_)
        : obj(obj_)
        , value(value_)
    {}

    void Execute()
    {
        boost::any newValue = value;
        obj->setProperty("direction", value);
    }

    std::string GetType()
    {
        return "IMovableLocationSetFunc";
    }

private:
    UObject_Ptr                                     obj;
    int                                             value;
};

#endif /* _I_ROTABLE_SET_DIRECTION_CLASS_H_ */
