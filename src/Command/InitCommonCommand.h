#ifndef _INIT_COMMON_COMMAND_H_
#define _INIT_COMMON_COMMAND_H_

#include <string>
#include <iostream>

#include "Command/ICommand.h"
#include "Command/ClassFunctionInitCommonCommand.h"

class InitCommonCommand: public ICommand
{
public:

    virtual ~InitCommonCommand() {}

    void Execute() override;

    std::string GetType() override;

private:
    ClassFunctionInitCommonCommand                          classFunction;
};

#endif /* _INIT_COMMON_COMMAND_H_ */
