#ifndef _SPACE_SHIP_H_
#define _SPACE_SHIP_H_

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

#include "Common/UObject.h"
#include "Exception/UobjectException.h"

class SpaceShip: public UObject
{
public:

	SpaceShip()
	{
		mapKey["position_x"] = 0;
		mapKey["position_y"] = 0;
		mapKey["velocity_x"] = 0;
		mapKey["velocity_y"] = 0;
		mapKey["direction"] = 0;
		mapKey["angleRotate"] = 0;
		mapKey["shotRange"] = 0;
		mapKey["health"] = 0;
	}

	virtual ~SpaceShip() {};

	/// [out] - error
	/// [in] nameProperty
	/// [out] value
	boost::any getProperty(const std::string &nameProperty) override
	{
		auto iter = mapKey.find(nameProperty);
		if (iter == mapKey.end())
			throw UobjectException("Uobject parameter of key isn't exist");

		return iter->second;
	}

	void setProperty(const std::string &nameProperty, boost::any newValue) override
	{
		auto iter = mapKey.find(nameProperty);
		if (iter == mapKey.end())
			throw UobjectException("Uobject parameter of key isn't exist");

		iter->second = newValue;
	}

	int getNumberProperty()
	{
		return mapKey.size();
	}

	boost::any getPropertyIter(unsigned int iter, std::string &nameProperty)
	{
		if (mapKey.size() - iter < 1)
			throw UobjectException("Uobject parameter of key isn't exist");

		std::unordered_map<std::string, boost::any>::iterator it = mapKey.begin();
		std::advance (it,iter);

		nameProperty = it->first;
		return it->second;
	}

private:

	std::unordered_map<std::string, boost::any> mapKey;
};

#endif /* _SPACE_SHIP_H_ */
