#ifndef _I_MOVABLE_LOCATION_SET_CLASS_H_
#define _I_MOVABLE_LOCATION_SET_CLASS_H_


#include "../../Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/UobjectException.h"

class IMovableLocationSetClass: public ICommand
{
public:

    virtual ~IMovableLocationSetClass(){}

    IMovableLocationSetClass(UObject_Ptr obj_, std::vector<int> value_)
        : obj(obj_)
        , value(value_)
    {}

    void Execute()
    {
        if (value.size() != 2)
            throw UobjectException("Uobject parameter value for set isn't correct");

        boost::any newValue = value[0];
        obj->setProperty("position_x", newValue);
        newValue = value[1];
        obj->setProperty("position_y", newValue);
    }

    std::string GetType()
    {
        return "IMovableLocationSetFunc";
    }

private:
    UObject_Ptr                                     obj;
    std::vector<int>                                value;
};

#endif /* _I_MOVABLE_LOCATION_SET_CLASS_H_ */
