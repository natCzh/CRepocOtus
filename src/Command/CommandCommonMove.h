#ifndef _COMMAND_COMMON_MOVE_H_
#define _COMMAND_COMMON_MOVE_H_

#include "ICommand.h"
#include "Common/QueueCommand.h"

class CommandLogger: public ICommand
{
public:

	CommandLogger(const std::string &strExecute)
		: dataExecute(strExecute)
	{}

	void Execute() override
	{
		std::cout << "dataExecute - " << dataExecute << std::endl;
	}

	std::string GetType() override
	{
		return "CommandLogger";
	}

	void SetDataExecute(const std::string &strExecut)
	{
		dataExecute = strExecut;
	}

private:
	std::string					dataExecute;
};

class CommandAddQueueEnd: public ICommand
{
public:

	CommandAddQueueEnd(const QueueCommand &qCommand, std::shared_ptr<ICommand> commandCur)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
		, command(commandCur)
	{}

	CommandAddQueueEnd(const QueueCommand &qCommand)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
	{}

	void Execute() override
	{
		qCommand->Push(command);
	}

	std::string GetType() override
	{
		return "CommandAddQueueEnd";
	}

	std::shared_ptr<ICommand>									command;

private:
	std::shared_ptr<QueueCommand>								qCommand;
};

class CommandRepeat: public ICommand
{
public:

	CommandRepeat(std::shared_ptr<QueueCommand> qCommand_, std::shared_ptr<ICommand> commandCur)
		: qCommand(qCommand_)
		, command(commandCur)
	{}

	CommandRepeat(const QueueCommand &qCommand)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
	{}

	void Execute() override
	{
		command->Execute();
	}

	std::string GetType() override
	{
		return "CommandRepeat";
	}

	std::shared_ptr<ICommand>									command;

private:
	std::shared_ptr<QueueCommand>								qCommand;
};

class CommandRepeatTwo: public ICommand
{
public:

	CommandRepeatTwo(const QueueCommand &qCommand, std::shared_ptr<ICommand> commandCur)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
		, command(commandCur)
	{}

	CommandRepeatTwo(const QueueCommand &qCommand)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
	{}

	void Execute() override
	{
		command->Execute();
	}

	std::string GetType() override
	{
		return "CommandRepeatTwo";
	}

	std::shared_ptr<ICommand>									command;

private:
	std::shared_ptr<QueueCommand>								qCommand;
};

#endif _COMMAND_COMMON_MOVE_H_