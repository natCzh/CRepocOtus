#ifndef _DEPENDENCY_RESOLVE_H_
#define _DEPENDENCY_RESOLVE_H_

#include <string>
#include <unordered_map>
#include <functional>

#include "src/scopes/IDependencyResolve.h"
#include "src/Command/ICommand.h"

namespace Scopes
{
	class DependencyResolve: public IDependencyResolve
	{
	public:

		ICommand_Ptr Resolve(const std::string &key, UObject *obj)
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
		}

	private:

		std::unordered_map<std::string, ICommand_Ptr>					scope;
	};
}

#endif /* _DEPENDENCY_RESOLVE_H_ */