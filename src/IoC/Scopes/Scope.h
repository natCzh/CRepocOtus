#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <string>
#include <unordered_map>
#include <boost/any.hpp>

#include "Exception/IoCException.h"

namespace Scopes
{
	class Scope
	{
	public:

		Scope() {}

		Scope(const Scope &orig)
			: scopeMap(orig.scopeMap)
		{}

		Scope& operator=(const Scope &orig)
		{
			this->scopeMap = orig.scopeMap;

			return *this;
		}

		boost::any GetValueOrDefault(const std::string &key)
		{
			auto iterF = scopeMap.find(key);
			if (iterF != scopeMap.end())
				return iterF->second;
			else
				throw IoCException("IoC parameter of key isn't exist");
		}
		
		void Add(const std::string &key, boost::any &dependence)
		{
			scopeMap[key] = dependence;
		}



	private:

		std::unordered_map<std::string, boost::any >					scopeMap; 
	};
}

#endif /* _SCOPE_H_ */
