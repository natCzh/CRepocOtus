#ifndef _I_SHOTABLE_SET_NUMBER_SHOT_CLASS_H_
#define _I_SHOTABLE_SET_NUMBER_SHOT_CLASS_H_

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"

class IShotableSetNumberShotClass: public ICommand
{
public:

    virtual ~IShotableSetNumberShotClass(){}

    IShotableSetNumberShotClass(UObject_Ptr obj_, int value_)
        : obj(obj_)
        , value(value_)
    {}

    void Execute()
    {
        boost::any newValue = value;
        obj->setProperty("numberShot", value);
    }

    std::string GetType()
    {
        return "IShotableSetNumberShotClass";
    }

private:
    UObject_Ptr                                     obj;
    int                                             value;
};

#endif /* _I_SHOTABLE_SET_NUMBER_SHOT_CLASS_H_ */

