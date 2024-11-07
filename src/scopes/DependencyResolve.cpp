#include <string>

#include "scopes/DependencyResolve.h"
#include "Command/ICommand.h"
#include "Exception/ScopesException.h"

std::shared_ptr<Scopes::Scope> Scopes::DependencyResolve::currentScope = std::make_shared<Scopes::Scope>();
std::unordered_map<int, std::shared_ptr<Scopes::Scope> > Scopes::DependencyResolve::scopes{ { 0, Scopes::DependencyResolve::currentScope} };

Scopes::DependencyResolve::DependencyResolve()
{
	currentScope = std::make_shared<Scopes::Scope>();
	scopes[0] = currentScope;
	Init(currentScope);
}

void Scopes::DependencyResolve::Init(std::shared_ptr<Scopes::Scope> scopeCur)
{
	// "Scopes.Current.Set"
	std::function<void(std::shared_ptr<Scopes::Scope>)> fun = std::bind(&Scopes::DependencyResolve::SetCurrentScope, this, std::placeholders::_1);
	boost::any v = fun;
	scopeCur->Add("Scopes.Current.Set", v);

	//"Scopes.Create.Empty"
	std::function<std::shared_ptr<Scopes::Scope>(int)> funEmpty = std::bind(&Scopes::DependencyResolve::NewScopeEmpty, this, std::placeholders::_1);
	boost::any vEmpty = funEmpty;
	scopeCur->Add("Scopes.Create.Empty", vEmpty);

	//"Scopes.Create.Root"
	std::function<std::shared_ptr<Scopes::Scope>(int)> funNewRoot = std::bind(&Scopes::DependencyResolve::NewScopeRoot, this, std::placeholders::_1);
	boost::any vNewRoot = funNewRoot;
	scopeCur->Add("Scopes.Create.Root", vNewRoot);

	//"Scopes.Current"
	std::function<std::shared_ptr<Scopes::Scope>()> funCurrent = std::bind(&Scopes::DependencyResolve::GetCurrentScope, this);
	boost::any vCurrent = funCurrent;
	scopeCur->Add("Scopes.Current", vCurrent);

	//"Scopes.Delete"
	std::function<void(int)> funDel = std::bind(&Scopes::DependencyResolve::DeleteScope, this, std::placeholders::_1);
	boost::any vDel = funDel;
	scopeCur->Add("Scopes.Delete", vDel);

	//"Scopes.Current.Clear"
	std::function<void()> funCurClear = std::bind(&Scopes::DependencyResolve::ClearCurrentScopeCommand, this);
	boost::any vCurClear = funCurClear;
	scopeCur->Add("Scopes.Current.Clear", vCurClear);

	// "Scopes.Current.SetId"
	std::function<void(size_t)> funCurSetId = std::bind(&Scopes::DependencyResolve::SetCurrentScopeId, this, std::placeholders::_1);
	boost::any vCurSetId = funCurSetId;
	scopeCur->Add("Scopes.Current.SetId", vCurSetId);
}

/// "Scopes.Current.Set"
void Scopes::DependencyResolve::SetCurrentScope(std::shared_ptr<Scopes::Scope> scopeCur_)
{
	std::unique_lock<std::mutex> lock(this->mutex);
	currentScope = scopeCur_;
}

/// "Scopes.Current.SetId"
void Scopes::DependencyResolve::SetCurrentScopeId(size_t idScope)
{
	std::unique_lock<std::mutex> lock(this->mutex);
	if (scopes.find(idScope) == scopes.end())
		throw ScopesException("Scopes with this id isn't exist");
	currentScope = scopes.find(idScope)->second;
}

/// "Scopes.Create.Empty"
std::shared_ptr<Scopes::Scope> Scopes::DependencyResolve::NewScopeEmpty(int idScope)
{
	std::unique_lock<std::mutex> lock(this->mutex);
	if (scopes.find(idScope) != scopes.end())
		throw ScopesException("Scopes with this id is exist");
	scopes[idScope] = std::shared_ptr<Scopes::Scope>(new Scopes::Scope());
	return scopes[idScope];
}

/// "Scopes.Create.Root"
std::shared_ptr<Scopes::Scope> Scopes::DependencyResolve::NewScopeRoot(int idScope)
{
	std::unique_lock<std::mutex> lock(this->mutex);
	if (scopes.find(idScope) != scopes.end())
		throw ScopesException("Scopes with this id is exist");;
	scopes[idScope] = std::shared_ptr<Scopes::Scope>(new Scopes::Scope());
	Init(scopes[idScope]);
	return scopes[idScope];
}

/// "Scopes.Current.Clear"
void Scopes::DependencyResolve::ClearCurrentScopeCommand()
{
	std::unique_lock<std::mutex> lock(this->mutex);
	currentScope = nullptr;
}

/// "Scopes.Current"
std::shared_ptr<Scopes::Scope> Scopes::DependencyResolve::GetCurrentScope()
{
	return currentScope;
}

/// "Scopes.Delete"
void Scopes::DependencyResolve::DeleteScope(int idScope)
{
	std::unique_lock<std::mutex> lock(this->mutex);
	auto delScope = scopes.find(idScope);
	if (scopes.find(idScope) != scopes.end())
		throw ScopesException("Scopes with this id is exist");;
	scopes.erase(delScope);
}



