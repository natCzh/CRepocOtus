#ifndef _INTERPRET_COMMAND_EXCEPTION_H_
#define _INTERPRET_COMMAND_EXCEPTION_H_

#include <exception>
#include <string>

class InterpretCommandException: public std::exception
{
public:
	InterpretCommandException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// сообщение об ошибке
};

#endif /* _INTERPRET_COMMAND_EXCEPTION_H_ */
