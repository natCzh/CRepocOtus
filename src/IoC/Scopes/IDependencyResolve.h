#ifndef _I_DEPENDENCY_RESOLVE_H_
#define _I_DEPENDENCY_RESOLVE_H_

#include <string>

namespace Scopes
{
	class IDependencyResolve
	{
	public:

		virtual ~IDependencyResolve() {}
		
		// template<typename T, typename... Args>
		// T Resolve(std::string key, Args... args) { return nullptr; }
	};
}

#endif /* _I_DEPENDENCY_RESOLVE_H_ */