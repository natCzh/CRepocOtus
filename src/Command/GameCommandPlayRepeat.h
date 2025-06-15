#ifndef _GAME_COMMAND_PLAY_REPEAT_H_
#define _GAME_COMMAND_PLAY_REPEAT_H_

#include "ICommand.h"
#include "Common/ThreadDeque.h"
#include "Command/IBridgeCommand.h"

// команда, которая повторяется в
class GameCommandPlayRepeat: public ICommand, public IBridgeCommand
{
public:

    GameCommandPlayRepeat(std::shared_ptr<ThreadDeque<ICommand_Ptr> > collection_ptr_, ICommand_Ptr cmd_)
        : collection_ptr(collection_ptr_)
        , cmd(cmd_)
    {}

    virtual ~GameCommandPlayRepeat() {}

    void Execute() override
    {
        cmd->Execute();
        collection_ptr->push(cmd);
    }

    void Inject(ICommand_Ptr injectableCommand) override
    {
        cmd = injectableCommand;
    }

    std::string GetType() override
    {
        return "GameCommandPlayRepeat";
    }

private:

    std::shared_ptr<ThreadDeque<ICommand_Ptr> >                       collection_ptr;
    ICommand_Ptr                                                      cmd;
};

#endif /* _GAME_COMMAND_PLAY_REPEAT_H_ */
