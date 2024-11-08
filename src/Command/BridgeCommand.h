#ifndef _BRIDGE_COMMAND_H_
#define _BRIDGE_COMMAND_H_

#include "Command/ICommand.h"

class BridgeCommand : public ICommand
{
public:
	BridgeCommand(ICommand_Ptr cmd_)
		: cmd(cmd_)
	{}

	void Inject(ICommand_Ptr injectableCommand)
	{
		cmd = injectableCommand;
	}

	void Execute()
	{
		cmd->Execute();
	}

	std::string GetType()
	{
		return "BridgeCommand";
	}

protected:
	
	ICommand_Ptr cmd;
};

#endif /* _BRIDGE_COMMAND_H_ */