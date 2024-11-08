#ifndef _U_OBJECT_EXCEPTION_H_
#define _U_OBJECT_EXCEPTION_H_

#include <exception>
#include <string>

// "Uobject parameter of key isn't exist"  - по данному ключу нету параметров

class UobjectException: public std::exception
{
public:
	UobjectException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// сообщение об ошибке
};

#endif /* _U_OBJECT_EXCEPTION_H_ */
