#ifndef _SCOPES_EXCEPTION_H_
#define _SCOPES_EXCEPTION_H_

#include <exception>
#include <string>

// "Scopes with this id is exist"  - �� ������� �� ����� ����� ��� ����������

class ScopesException: public std::exception
{
public:
	ScopesException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// ��������� �� ������
};

#endif /* _SCOPES_EXCEPTION_H_ */
