#ifndef _I_BRIDGE_COMMAND_H_
#define _I_BRIDGE_COMMAND_H_

#include <string>
#include <iostream>

#include "Command/ICommand.h"

class IBridgeCommand
{
public:

    virtual ~IBridgeCommand();

    virtual void Execute() = 0;

    virtual void Inject(ICommand_Ptr injectableCommand) = 0;
};

#endif /* _I_BRIDGE_COMMAND_H_ */
