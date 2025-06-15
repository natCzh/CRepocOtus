#ifndef _COMMAND_MOVE_LONG_OPERATION_H_
#define _COMMAND_MOVE_LONG_OPERATION_H_

#include <QDebug>

#include "IoC/IoC.h"

#include "../../Command/ICommand.h"
#include "../../Command/IBridgeCommand.h"
#include "../../Command/BridgeCommand.h"
#include "../../Command/CommandRepeat.h"
#include "../../Command/CommandEmpty.h"
#include "../../Command/SimpleMacroCommand.h"

extern IoC* ioc;
class CommandMoveLongOperation: public ICommand, public IBridgeCommand
{
public:
    CommandMoveLongOperation(size_t idObj, std::shared_ptr<QueueCommand> qCommand_)
    {
        ICommand_Ptr cmdBr = std::make_shared<CommandEmpty>();
        bridgeCommand = std::make_shared<BridgeCommand>(cmdBr);
        repeatCommand = std::make_shared<CommandRepeat>(qCommand_, bridgeCommand);
        ICommand_Ptr movement = ioc->Resolve<ICommand_Ptr>("Command.Movement", idObj);
        std::vector<ICommand_Ptr> cmdsVect{movement, repeatCommand};
        macroCmd = std::make_shared<SimpleMacroCommand>(cmdsVect);
        bridgeCommand->Inject(macroCmd);
    }

    virtual ~CommandMoveLongOperation(){}

    void Execute() override
    {
        qDebug() << QString::fromStdString(GetType());
        macroCmd->Execute();
    }

    std::string GetType() override
    {
        return "Command.MoveLongOperation";
    }

    void Inject(ICommand_Ptr injectableCommand) override
    {
        bridgeCommand->Inject(injectableCommand);
    }

private:
    std::shared_ptr<BridgeCommand>                                       bridgeCommand;
    std::shared_ptr<CommandRepeat>                                       repeatCommand;
    ICommand_Ptr                                                         macroCmd;
};

#endif /* _COMMAND_MOVE_LONG_OPERATION_H_ */
