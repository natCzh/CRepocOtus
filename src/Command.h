#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "src/ICommand.h"
#include "src/QueueCommand.h"

class CommandLogger: public ICommand
{
public:

	CommandLogger(const std::string &strExecute)
		: dataExecute(strExecute)
	{}

	int Execute() override
	{
		std::cout << "dataExecute - " << dataExecute << std::endl;

		return 0;
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

	int Execute() override
	{
		qCommand->Push(command);
		return 0;
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

	CommandRepeat(const QueueCommand &qCommand, std::shared_ptr<ICommand> commandCur)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
		, command(commandCur)
	{}

	CommandRepeat(const QueueCommand &qCommand)
		: qCommand(std::make_shared<QueueCommand>(qCommand))
	{}

	int Execute() override
	{
		return command->Execute();
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

	int Execute() override
	{
		return command->Execute();
	}

	std::string GetType() override
	{
		return "CommandRepeatTwo";
	}

	std::shared_ptr<ICommand>									command;

private:
	std::shared_ptr<QueueCommand>								qCommand;
};

#endif _COMMAND_H_