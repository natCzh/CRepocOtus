#ifndef _SET_CURRENT_SCOPE_COMMAND_H_
#define _SET_CURRENT_SCOPE_COMMAND_H_

#include <memory>

#include "src/ICommand.h"
#include "src/scopes/DependencyResolve.h"

class SetCurrentScopeCommand: public ICommand
{
	SetCurrentScopeCommand(std::shared_ptr<DependencyResolve> scope)
		: _scope(scope)
	{}

	int Execute()
	{

	}


protected:
	std::shared_ptr<DependencyResolve>					_scope;
};

#endif /* _SET_CURRENT_SCOPE_COMMAND_H_ */