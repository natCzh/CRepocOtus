#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include "src/scopes/IDependencyResolve.h"
#include "src/Command/ICommand.h"
#include "Common/UObject.h"

namespace Scopes
{
	class Scope: public IDependencyResolve
	{
	public:

		ICommand_Ptr Resolve(const std::string &key, UObject *obj)
		{
			// ICommand_Ptr

			return scopeIComand.begin()->second;
		}

		void dependencyResolve(std::unordered_map<std::string, ICommand_Ptr> &scopeCur)
		{
			// проверки на родительский скоуп нету
			scopeIComand = scopeCur;
		}

		ICommand_Ptr GetValueOrDefault(const std::string &key)
		{
			auto iterF = scopeIComand.find(key);
			if (iterF != scopeIComand.end())
				return iterF->second;
			else
				return nullptr;
		}
		
		void AddCommand(const std::string &key, ICommand_Ptr command) override
		{
			scopeIComand[key] = command;
		}

	private:

		// TOOD пока тут будет много мапов, потом переделать !!!!!! или boost или cсвю any сюда впихнуть 
		std::unordered_map<std::string, ICommand_Ptr >					scopeIComand; 
	};
}

#endif /* _SCOPE_H_ */
