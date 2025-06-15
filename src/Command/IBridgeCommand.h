#ifndef _I_BRIDGE_COMMAND_H_
#define _I_BRIDGE_COMMAND_H_

#include "Command/ICommand.h"

class IBridgeCommand
{
public:

    virtual ~IBridgeCommand(){}

    virtual void Execute() = 0;

    virtual void Inject(ICommand_Ptr injectableCommand) = 0;
};

using IBridgeCommand_Ptr = std::shared_ptr<IBridgeCommand>;

#endif /* _I_BRIDGE_COMMAND_H_ */
