#ifndef _COMMAND_EMPTY_H_
#define _COMMAND_EMPTY_H_

#include "Command/ICommand.h"

class CommandEmpty: public ICommand
{
public:

    CommandEmpty()
    {}

    virtual ~CommandEmpty() {}

    void Execute() override {}

    std::string GetType() override { return "CommandEmpty"; }
};

#endif /* _COMMAND_EMPTY_H_ */
