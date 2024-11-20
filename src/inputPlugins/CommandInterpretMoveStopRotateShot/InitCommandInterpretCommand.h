#ifndef _INIT_COMMAND_INTERPRET_COMMAND_H_
#define _INIT_COMMAND_INTERPRET_COMMAND_H_

#include "Command/ICommand.h"
#include "ClassFunctionInitCommandInterpret.h"

class InitCommandInterpretCommand: public ICommand
{
public:

    virtual ~InitCommandInterpretCommand() {}

    void Execute() override;

    std::string GetType() override;

private:
    ClassFunctionInitCommandInterpret                          classFunction;
};

#endif /* _INIT_COMMAND_INTERPRET_COMMAND_H_ */
