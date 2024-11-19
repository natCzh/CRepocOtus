#ifndef _CLASS_FUNCTION_INIT_COMMON_COMMAND_H_
#define _CLASS_FUNCTION_INIT_COMMON_COMMAND_H_

#include <string>
#include <vector>

#include "Command/ICommand.h"
#include "Command/SimpleMacroCommand.h"

class ClassFunctionInitCommonCommand
{
public:
    ClassFunctionInitCommonCommand(){}
    virtual ~ClassFunctionInitCommonCommand() {}

    ICommand_Ptr CommandSimpleMacroCommand(const std::vector<std::shared_ptr<ICommand> > &cmds_value)
    {
        return ICommand_Ptr(new SimpleMacroCommand(cmds_value));
    }

};

#endif /* _CLASS_FUNCTION_INIT_COMMON_COMMAND_H_ */
