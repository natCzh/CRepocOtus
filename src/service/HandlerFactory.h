#ifndef _HANDLER_INSTANCE_H_
#define _HANDLER_INSTANCE_H_

#include "StoreDict.h"
#include "src/Command/CommandCommonMove.h"
#include "src/Command/CommandErrorDefault.h"

class HandlerErrorDefault
{

public:
	HandlerErrorDefault()
		: m_defaultCommand()
	{}

	ICommand_Ptr process(ICommand_Ptr c, const std::exception &)
	{
		return std::make_shared<CommandErrorDefault>(m_defaultCommand);
	}

private:
	CommandErrorDefault						m_defaultCommand;
}; 

class HandlerLogQueue
{

public:
	HandlerLogQueue(const QueueCommand &qCommand)
		: m_defaultCommand(qCommand)
	{}

	ICommand_Ptr process(ICommand_Ptr c, const std::exception &e)
	{
		m_defaultCommand.command = c;
		return std::make_shared<CommandAddQueueEnd>(m_defaultCommand);
	}

private:
	CommandAddQueueEnd						m_defaultCommand;
}; 

class HandlerRepeat
{

public:
	HandlerRepeat(const QueueCommand &qCommand)
		: m_defaultCommand(qCommand)
	{}

	ICommand_Ptr process(ICommand_Ptr c, const std::exception &e)
	{
		m_defaultCommand.command = c;
		return std::make_shared<CommandRepeat>(m_defaultCommand);
	}

private:
	CommandRepeat						m_defaultCommand;
}; 

class HandlerRepeatAndLog
{
public:
	HandlerRepeatAndLog(const QueueCommand &qCommand)
		: m_defaultCommand(qCommand)
		, m_logger("")
	{}

	ICommand_Ptr process(ICommand_Ptr c, const std::exception &e)
	{
		if (auto comCur_ptr = dynamic_cast<CommandRepeat*>(c.get()))
		{
			m_logger.SetDataExecute(e.what());
			return std::make_shared<CommandLogger>(m_logger);
		}
		else
		{
			m_defaultCommand.command = c;
			return std::make_shared<CommandRepeat>(m_defaultCommand);
		}
	}

private:
	CommandRepeat						m_defaultCommand;
	CommandLogger						m_logger;
}; 

class HandlerRepeatTwoAndLog
{
public:
	HandlerRepeatTwoAndLog(const QueueCommand &qCommand)
		: m_defaultCommand(qCommand)
		, m_commandTwo(qCommand)
		, m_logger("")
	{}

	ICommand_Ptr process(ICommand_Ptr c, const std::exception &e)
	{
		if (auto comCur_ptr = dynamic_cast<CommandRepeat*>(c.get()))
		{
			m_commandTwo.command = c;
			return std::make_shared<CommandRepeatTwo>(m_commandTwo);
		}
		if (auto comCur_ptr = dynamic_cast<CommandRepeatTwo*>(c.get()))
		{
			m_logger.SetDataExecute(e.what());
			return std::make_shared<CommandLogger>(m_logger);
		}
		else
		{
			m_defaultCommand.command = c;
			return std::make_shared<CommandRepeat>(m_defaultCommand);
		}
	}

private:
	CommandRepeat						m_defaultCommand;
	CommandRepeatTwo					m_commandTwo;
	CommandLogger						m_logger;
}; 

#endif _HANDLER_INSTANCE_H_