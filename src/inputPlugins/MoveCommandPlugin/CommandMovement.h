#ifndef _COMMAND_MOVEMENT_H_
#define _COMMAND_MOVEMENT_H_

#include <vector>
#include <cstring>

#include "../../Command/ICommand.h"
#include "IoC/IoC.h"
#include "CommonLib/UObject.h"
#include "Command/SimpleMacroCommand.h"

extern IoC* ioc;
class CommandMovement: public ICommand
{
public:
    CommandMovement(size_t idObject_)
        : idObject(idObject_)
    {}

    void Execute() override
    {
        std::unordered_map<unsigned long long, std::vector<std::string> > commandsDescMap = ioc->Resolve<std::unordered_map<unsigned long long, std::vector<std::string> > >("Description.Movement");
        std::vector<std::string> commandsDesc = commandsDescMap.find(idObject)->second;

        std::unordered_map<unsigned long long, UObject_Ptr> curVectObject = ioc->Resolve<std::unordered_map<unsigned long long, UObject_Ptr> >(
            "GameItems");
        UObject_Ptr obj = curVectObject.find(idObject)->second;

        std::vector<ICommand_Ptr> cmdsVect;
        for (auto iter = commandsDesc.begin(); iter != commandsDesc.end(); iter++)
            cmdsVect.push_back(ioc->Resolve<ICommand_Ptr>(*iter, idObject));

        SimpleMacroCommand cmdMacro(cmdsVect);
        cmdMacro.Execute();
        std::cout << "Movement idObj " << idObject << std::endl;
        //ioc->Resolve<ICommand_Ptr>("Command.SimpleMacroCommand", cmdsVect)->Execute();
    }

    std::string GetType() override
    {
        return "Command.Movement";
    }

private:
    size_t                                      idObject;
};

#endif /* _COMMAND_MOVEMENT_H_ */
