#ifndef _DEPENDENCY_RESOLVE_H_
#define _DEPENDENCY_RESOLVE_H_

#include <unordered_map>
#include <memory>
#include <mutex>

#include "scopes/IDependencyResolve.h"
#include "scopes/Scope.h"

namespace Scopes
{
	class DependencyResolve: public IDependencyResolve
	{
	public:

		DependencyResolve();

		template<typename T, typename... Args>
		T Resolve(std::string key, Args... args);

		void Init();

		// работа со скоупами
		void SetCurrentScope(std::shared_ptr<Scopes::Scope> scopeCur_);
		void ClearCurrentScopeCommand();
		std::shared_ptr<Scopes::Scope> GetCurrentScope();
	
		/*ICommand_Ptr Resolve(const std::string &key, UObject *obj)
		{
			// ICommand_Ptr
			return scope.begin()->second;
		}

		void dependencyResolve(std::unordered_map<std::string, ICommand_Ptr> &scopeCur)
		{
			// проверки на родительский скоуп нету
			scope = scopeCur;
		}

		ICommand_Ptr GetValueOrDefault(const std::string &key)
		{
			auto iterF = scope.find(key);
			if (iterF != scope.end())
				return iterF->second;
			else
				return nullptr;
		}
		
		void AddCommand(const std::string &key, ICommand_Ptr command) override
		{
			scope[key] = command;
		}*/





	private:

		static std::shared_ptr<Scopes::Scope>											currentScope;
		static std::unordered_map<int, std::shared_ptr<Scopes::Scope> >					scopes;
		std::mutex																		mutex;
	};
}

#endif /* _DEPENDENCY_RESOLVE_H_ */