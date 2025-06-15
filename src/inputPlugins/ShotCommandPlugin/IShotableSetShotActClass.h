#ifndef _I_SHOTABLE_SET_SHOT_ACT_CLASS_H_
#define _I_SHOTABLE_SET_SHOT_ACT_CLASS_H_

#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"

class IShotableSetShotActClass: public ICommand
{
public:

    virtual ~IShotableSetShotActClass(){}

    IShotableSetShotActClass(UObject_Ptr obj_, int value_)
        : obj(obj_)
        , value(value_)
    {}

    void Execute()
    {
        boost::any newValue = value;
        obj->setProperty("shotAct", value);
    }

    std::string GetType()
    {
        return "IShotableSetShotActClass";
    }

private:
    UObject_Ptr                                     obj;
    int                                             value;
};

#endif /* _I_SHOTABLE_SET_SHOT_ACT_CLASS_H_ */
