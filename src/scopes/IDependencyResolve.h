#ifndef _I_DEPENDENCY_RESOLVE_H_
#define _I_DEPENDENCY_RESOLVE_H_

#include <string>

#include "src/UObject.h"

namespace Scopes
{
	class IDependencyResolve
	{
	public:
		template<typename T>
		T* Resolve(const std::string &key, UObject *obj);
	};
}

#endif /* _I_DEPENDENCY_RESOLVE_H_ */