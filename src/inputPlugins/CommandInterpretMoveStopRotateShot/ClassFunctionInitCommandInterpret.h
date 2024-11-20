#ifndef _CLASS_FUNCTION_INIT_COMMAND_INTERPRET_H_
#define _CLASS_FUNCTION_INIT_COMMAND_INTERPRET_H_

#include "Command/ICommand.h"
#include "../../CommonLib/UObject.h"
#include "../../CommonLib/IMessagable.h"
#include "CommandInterpretCommand_PrepareForMove.h"
#include "CommandInterpretCommand_StartMove.h"
#include "CommandInterpretCommand_PrepareForStopMove.h"
#include "CommandInterpretCommand_StopMove.h"

class ClassFunctionInitCommandInterpret
{
public:
    ClassFunctionInitCommandInterpret(){}
    virtual ~ClassFunctionInitCommandInterpret() {}

    ICommand_Ptr CommandPrepareForMove(UObject_Ptr obj, IMessagable_Ptr messagable)
    {
         return std::make_shared<CommandInterpretCommand_PrepareForMove>(obj, messagable);
    }

    ICommand_Ptr CommandInterpretCommandStartMove(IMessagable_Ptr messagable, std::shared_ptr<QueueCommand> queue)
    {
        return std::make_shared<CommandInterpretCommand_StartMove>(messagable, queue);
    }

    ICommand_Ptr CommandPrepareForStopMove(UObject_Ptr obj)
    {
        return std::make_shared<CommandInterpretCommand_PrepareForStopMove>(obj);
    }

    ICommand_Ptr CommandInterpretCommandStopMove(IMessagable_Ptr messagable)
    {
        return std::make_shared<CommandInterpretCommand_StopMove>(messagable);
    }
};

#endif /* _CLASS_FUNCTION_INIT_COMMAND_INTERPRET_H_ */
