#include <string>

#include "scopes/DependencyResolve.h"
#include "Command/ICommand.h"

std::shared_ptr<Scopes::Scope> Scopes::DependencyResolve::currentScope = std::make_shared<Scopes::Scope>();
std::unordered_map<int, std::shared_ptr<Scopes::Scope> > Scopes::DependencyResolve::scopes{ { 0, Scopes::DependencyResolve::currentScope} };

Scopes::DependencyResolve::DependencyResolve()
{
	currentScope = std::make_shared<Scopes::Scope>();
	scopes[0] = currentScope;
}

void Scopes::DependencyResolve::Init()
{
	std::unique_lock<std::mutex> lock(this->mutex);
	//scopes[0]->Add()
}

void Scopes::DependencyResolve::SetCurrentScope(std::shared_ptr<Scopes::Scope> scopeCur_)
{
	std::unique_lock<std::mutex> lock(this->mutex);
	currentScope = scopeCur_;
}

void Scopes::DependencyResolve::ClearCurrentScopeCommand()
{
	std::unique_lock<std::mutex> lock(this->mutex);
	currentScope = nullptr;
}

std::shared_ptr<Scopes::Scope> Scopes::DependencyResolve::GetCurrentScope()
{
	return currentScope;
}



