#ifndef _COMMAND_REPEAT_H_
#define _COMMAND_REPEAT_H_

#include "Command/ICommand.h"
#include "Common/QueueCommand.h"

class CommandRepeat : public ICommand
{
public:
	CommandRepeat(std::shared_ptr<QueueCommand> qCommand_, std::shared_ptr<ICommand> commandCur)
		: command(commandCur)
		, qCommand(qCommand_)
	{}

	void Execute()
	{
		qCommand->Push(command);
	}

	std::string GetType()
	{
		return "CommandRepeat";
	}

private:
	std::shared_ptr<ICommand>									command;
	std::shared_ptr<QueueCommand>								qCommand;
};

#endif /* _COMMAND_REPEAT_H_ */