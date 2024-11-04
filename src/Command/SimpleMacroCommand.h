#ifndef _SIMPLE_MACRO_COMMAND_H_
#define _SIMPLE_MACRO_COMMAND_H_

#include <vector>

#include "Command/ICommand.h"

class SimpleMacroCommand : public ICommand
{
public:
	SimpleMacroCommand(const std::vector<std::shared_ptr<ICommand> > &cmds_value)
		: cmds(cmds_value)
	{}

	void Execute()
	{
		unsigned int sizeData = cmds.size();
		for (unsigned int it = 0; it < sizeData; it++)
			cmds[it]->Execute();
	}

	std::string GetType() override
	{
		return "SimpleMacroCommand";
	}

private:
	std::vector<std::shared_ptr<ICommand> > cmds;
};

#endif /* _SIMPLE_MACRO_COMMAND_H_*/