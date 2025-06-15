#ifndef _CLASS_FUNCTION_INIT_COMMON_COMMAND_H_
#define _CLASS_FUNCTION_INIT_COMMON_COMMAND_H_

#include <vector>

#include "Command/ICommand.h"
#include "Command/SimpleMacroCommand.h"

class ClassFunctionInitCommonCommand
{
public:
    ClassFunctionInitCommonCommand(){}
    virtual ~ClassFunctionInitCommonCommand() {}

    ICommand_Ptr CommandSimpleMacroCommand(const std::vector<ICommand_Ptr> &cmds_value)
    {
        return std::make_shared<SimpleMacroCommand>(cmds_value);
    }

};

#endif /* _CLASS_FUNCTION_INIT_COMMON_COMMAND_H_ */
