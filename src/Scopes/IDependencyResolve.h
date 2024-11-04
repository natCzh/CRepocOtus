#ifndef _I_DEPENDENCY_RESOLVE_H_
#define _I_DEPENDENCY_RESOLVE_H_

#include <string>

#include "Common/UObject.h"
#include "Command/ICommand.h"

namespace Scopes
{
	class IDependencyResolve
	{
	public:
		
		virtual ICommand_Ptr Resolve(const std::string &key, UObject *obj) = 0;

		virtual void AddCommand(const std::string &key, ICommand_Ptr command) = 0;
	};
}

#endif /* _I_DEPENDENCY_RESOLVE_H_ */