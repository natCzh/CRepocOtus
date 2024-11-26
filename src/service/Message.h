#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <boost/any.hpp>

#include "CommonLib/UObject.h"
#include "CommonLib/UobjectException.h"

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

        mapKey["typeObjs"] = 0; // vector<unsigned long long> тип объектов
        mapKey["idObjsNewGame"] = 0; // vector<unsigned long long> ид объектов
	}

	virtual ~Message() {};

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

    int getNumberProperty() override
	{
		return mapKey.size();
	}

    boost::any getPropertyIter(unsigned int iter, std::string &nameProperty) override
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

#endif /* _I_MESSAGE_H_ */
