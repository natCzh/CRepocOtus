#ifndef _INIT_COMMAND_H_
#define _INIT_COMMAND_H_

#include "src/ICommand.h"
#include "src/scopes/DependencyResolve.h"

namespace Scopes
{
	class InitCommand: public ICommand
	{
	public:
		int Execute()
		{
			return 0;

		}


	protected:
		
	};
}

#endif /* _INIT_COMMAND_H_ */