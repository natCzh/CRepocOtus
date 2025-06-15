#ifndef _SET_CURRENT_SCOPE_COMMAND_H_
#define _SET_CURRENT_SCOPE_COMMAND_H_

#include <memory>

#include "Command/ICommand.h"
#include "scopes/DependencyResolve.h"

class SetCurrentScopeCommand: public ICommand
{
	SetCurrentScopeCommand(std::shared_ptr<Scopes::DependencyResolve<ICommand_Ptr, Scopes::Scope> > depency_, std::shared_ptr<Scopes::Scope> scopeCur_)
		: depency(depency_)
		, scopeCur(scopeCur_)
	{}

	void Execute()
	{
		depency->SetCurrentScope(scopeCur);
	}

protected:
	std::shared_ptr<Scopes::DependencyResolve<ICommand_Ptr, Scopes::Scope> >					depency;
	std::shared_ptr<Scopes::Scope>																scopeCur;
};

#endif /* _SET_CURRENT_SCOPE_COMMAND_H_ */