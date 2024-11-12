#ifndef _SPACE_SHIP_H_
#define _SPACE_SHIP_H_

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

#include "CommonLib/UObject.h"
#include "Exception/UobjectException.h"

class SpaceShip: public UObject
{
public:

	SpaceShip()
	{
		mapKey["position_x"] = 0;
		mapKey["position_y"] = 0;
		mapKey["velocity"] = 0; // тут хранится модуль скорости
		mapKey["direction"] = 0; // хранится как часть от окружности , чтобы получить угол надо (d*360/n)
		mapKey["directionNumber"] = 4; // можно двигаться только в 4 стороны , те мы поделили окружность на 4 части
		mapKey["directionAngular"] = 0; // на сколько поворачиваемся
		
		mapKey["health"] = 0;

		// выстрел
		mapKey["shotRange"] = 0;
		mapKey["shotAct"] = 0; // был выстрел или нет у объекта
		mapKey["numberShot"] = 0; // кол-во выстрелов, патронов
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
