#ifndef _SPACE_SHIP_H_
#define _SPACE_SHIP_H_

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

#include "Common/UObject.h"

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
	/// [in-out] nameProperty
	/// [in-out] value
	int getProperty(const std::string &nameProperty, boost::any &value) override
	{
		auto iter = mapKey.find(nameProperty);
		if (iter == mapKey.end())
			return 1;

		value = iter->second;
		return 0;
	}

	int setProperty(const std::string &nameProperty, boost::any newValue) override
	{
		auto iter = mapKey.find(nameProperty);
		if (iter == mapKey.end())
			return 1;

		iter->second = newValue;
		return 0;
	}

	int getNumberProperty()
	{
		return mapKey.size();
	}

	int getPropertyIter(unsigned int iter, std::string &nameProperty, boost::any &value)
	{
		if (mapKey.size() - iter < 1)
			return 1;

		std::unordered_map<std::string, boost::any>::iterator it = mapKey.begin();
		std::advance (it,iter);

		nameProperty = it->first;
		value = it->second;

		return 0;
	}

private:

	std::unordered_map<std::string, boost::any> mapKey;
};

#endif /* _SPACE_SHIP_H_ */
