#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <boost/any.hpp>

#include "Common/UObject.h"

// Описание содержания сообщения
// Обязательные поля:
// id отправителя - ["id.Sender"] - тип - unsigned int
// id игры ["id.Game"] - тип - unsigned int
// id игрового объекта ["id.Object"] - тип - unsigned int
// id операции ["TypeCommand"] - тип - std::string
// Необязательные поля
// args ["args"] - вложенный json объект с параметрами операции - тип std::any

class Message: public UObject
{
public:
	Message()
	{
		mapKey["id.Sender"] = 0;
		mapKey["id.Game"] = 0;
		mapKey["id.Object"] = 0;
		mapKey["TypeCommand"] = 0;
		mapKey["args"] = NULL;
	}

	virtual ~Message() {};

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

#endif /* _I_MESSAGE_H_ */
