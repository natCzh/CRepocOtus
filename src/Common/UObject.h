#ifndef _U_OBJECT_H_
#define _U_OBJECT_H_

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

class UObject
{
public:
	/// [out] - error
	/// [in-out] nameProperty
	/// [in-out] value
	virtual int getProperty(const std::string &nameProperty, boost::any &value) = 0;
	virtual int setProperty(const std::string &nameProperty, boost::any newValue) = 0;

	virtual int getNumberProperty() = 0;
	virtual int getPropertyIter(unsigned int iter, std::string &nameProperty, boost::any &value) = 0;
};

class StateShip: public UObject
{
public:

	StateShip()
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

	virtual ~StateShip() {};

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

#endif /* _U_OBJECT_H_ */
