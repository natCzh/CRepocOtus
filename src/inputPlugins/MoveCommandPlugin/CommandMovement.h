#ifndef _COMMAND_MOVEMENT_H_
#define _COMMAND_MOVEMENT_H_

#include <vector>
#include <cstring>

#include "../../Command/ICommand.h"
#include "IoC/IoC.h"
#include "CommonLib/UObject.h"

extern IoC* ioc;
class CommandMovement: public ICommand
{
public:
    CommandMovement(size_t idObject_)
        : idObject(idObject_)
    {}

    void Execute() override
    {
        std::vector<std::string> commandsDesc = ioc->Resolve<std::vector<std::string> >("Description.Movement", idObject);
        UObject_Ptr obj = ioc->Resolve<UObject_Ptr>("GameItems", idObject);

        std::vector<ICommand_Ptr> cmdsVect;
        for (auto iter = commandsDesc.begin(); iter != commandsDesc.end(); iter++)
            cmdsVect.push_back(ioc->Resolve<ICommand_Ptr>(*iter, obj));

        ioc->Resolve<ICommand_Ptr>("Command.SimpleMacroCommand", cmdsVect)->Execute();
    }

    std::string GetType() override
    {
        return "Command.Movement";
    }

private:
    size_t                                      idObject;
};

#endif /* _COMMAND_MOVEMENT_H_ */
