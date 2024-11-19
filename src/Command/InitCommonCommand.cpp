#include <functional>
#include <boost/bind.hpp>

#include "Command/InitCommonCommand.h"

#include "IoC/IoC.h"

extern IoC* ioc;
void InitCommonCommand::Execute()
{
    std::vector<ICommand_Ptr> vectICommand;
    std::function<ICommand_Ptr(std::vector<ICommand_Ptr>)> funcMovement = boost::bind(&ClassFunctionInitCommonCommand::CommandSimpleMacroCommand, &classFunction, std::placeholders::_1);
    ioc->Resolve<ICommand_Ptr, ICommand_Ptr, std::string, std::function<ICommand_Ptr(std::vector<ICommand_Ptr>)> >(
                "IoC.Register",
                "Command.SimpleMacroCommand",
                funcMovement, vectICommand);
}

std::string InitCommonCommand::GetType()
{
    return "InitCommonCommand";
}
