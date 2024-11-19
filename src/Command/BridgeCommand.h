#ifndef _BRIDGE_COMMAND_H_
#define _BRIDGE_COMMAND_H_

#include "Command/ICommand.h"
#include "Command/IBridgeCommand.h"

class BridgeCommand : public ICommand, public IBridgeCommand
{
public:
	BridgeCommand(ICommand_Ptr cmd_)
		: cmd(cmd_)
	{}

    void Inject(ICommand_Ptr injectableCommand) override
	{
		cmd = injectableCommand;
	}

    void Execute() override
	{
		cmd->Execute();
	}

    std::string GetType() override
	{
		return "BridgeCommand";
	}

protected:
	
	ICommand_Ptr cmd;
};

#endif /* _BRIDGE_COMMAND_H_ */
