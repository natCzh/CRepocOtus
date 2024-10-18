#include "StatesQueueProcessing.h"
#include "queueProcessing.h"

bool SimpleStatesQueueProcessing::handle(queueProcessing *m)
{
	std::shared_ptr<ICommand> commandCur = queueCommand.GetCurrentCommand();
	if (!commandCur)
		return false;
	commandCur->Execute();
		
	if (commandCur->GetType() == "HardStop")
		m->set_currentState(ICommandStatesQueueProcessing_Ptr{nullptr});
	if (commandCur->GetType() == "MoveToCommand")
		m->set_currentState(ICommandStatesQueueProcessing_Ptr{new MoveToStatesQueueProcessing()});

	return true;
}

bool MoveToStatesQueueProcessing::handle(queueProcessing *m)
{
	std::shared_ptr<ICommand> commandCur = queueCommand.GetCurrentCommand();
	if (!commandCur)
		return false;
	queueCommandNew.Push(commandCur);
		
	if (commandCur->GetType() == "HardStop")
		m->set_currentState(ICommandStatesQueueProcessing_Ptr{nullptr});
	if (commandCur->GetType() == "RunCommand")
		m->set_currentState(ICommandStatesQueueProcessing_Ptr{new SimpleStatesQueueProcessing()});

	return true;
}