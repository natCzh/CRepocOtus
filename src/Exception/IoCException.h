#ifndef _I_O_C_EXCEPTION_H_
#define _I_O_C_EXCEPTION_H_

#include <exception>
#include <string>

class IoCException: public std::exception
{
public:
	IoCException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// ��������� �� ������
};

#endif /* _I_O_C_EXCEPTION_H_ */
