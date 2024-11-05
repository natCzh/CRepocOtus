#ifndef _I_DEPENDENCY_RESOLVE_H_
#define _I_DEPENDENCY_RESOLVE_H_

#include <string>

namespace Scopes
{

	class IDependencyResolve
	{
	public:
		
		template<typename T, typename... Args>
		T Resolve(std::string key, Args... args) {};
	};
}

#endif /* _I_DEPENDENCY_RESOLVE_H_ */