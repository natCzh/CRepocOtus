#ifndef _COMMAND_EXCEPTION_H_
#define _COMMAND_EXCEPTION_H_

#include <exception>
#include <string>

class CommandException: public std::exception
{
public:
	CommandException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// сообщение об ошибке
};

#endif /* _COMMAND_EXCEPTION_H_ */