#ifndef _SPACE_BATTLE_EXCEPTION_H_
#define _SPACE_BATTLE_EXCEPTION_H_s

#include <exception>
#include <string>

// "Gameid isn't exist"  - �� ������� �� ����� ����� ��� ����������

class SpaceBattleException: public std::exception
{
public:
	SpaceBattleException(const std::string &message)
		: message(message)
	{}

	const char* what() const noexcept override
	{
		return message.c_str();
	}

private:
	std::string									message;			// ��������� �� ������
};

#endif /* _SPACE_BATTLE_EXCEPTION_H_ */
