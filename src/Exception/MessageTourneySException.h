#ifndef _MESSAGE_TOURNEY_S_EXCEPTION_H_
#define _MESSAGE_TOURNEY_S_EXCEPTION_H_

#include <exception>
#include <string>

class MessageTourneySException: public std::exception
{
public:
	MessageTourneySException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// сообщение об ошибке
};

#endif /* _MESSAGE_TOURNEY_S_EXCEPTION_H_ */
