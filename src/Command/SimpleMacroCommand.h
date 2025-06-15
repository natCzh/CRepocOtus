#ifndef _SIMPLE_MACRO_COMMAND_H_
#define _SIMPLE_MACRO_COMMAND_H_

#include <vector>

#include "Command/ICommand.h"

class SimpleMacroCommand : public ICommand
{
public:
    SimpleMacroCommand(std::vector<ICommand_Ptr> cmds_value)
		: cmds(cmds_value)
	{}

    void Execute() override
	{
		unsigned int sizeData = cmds.size();
        for (auto iter = cmds.begin(); iter != cmds.end(); ++iter)
        //for (unsigned int it = 0; it < sizeData; it++)
            iter->get()->Execute();
	}

	std::string GetType() override
	{
		return "SimpleMacroCommand";
	}

private:
    std::vector<ICommand_Ptr> cmds;
};

#endif /* _SIMPLE_MACRO_COMMAND_H_*/
