#ifndef _INTERPRET_COMMAND_H_
#define _INTERPRET_COMMAND_H_

#include <memory>

#include "Command/ICommand.h"
#include "IoC/IoCGlobal.h"
#include "EndPoint/MessageAdapter.h"

// ������ � ������ �������(�������) �������� ������ �������
class InterpretCommand : public ICommand
{
public:

	InterpretCommand(std::shared_ptr<IMessagable> message_) 
		: massagable(message_)
	{}	

	virtual ~InterpretCommand() {}

	void Execute()
	{


		// ��� ���� �� IOC � massagable �������� �� �������, �� ��������� �� ���
		ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>(massagable->getTypeCommand(), massagable);
		// ��� ������� ����� �������� � �������, ��� ioc � ������� �������� � �������, �� � IOC ������ �������� �������

	}

	std::string GetType()
	{
		return "InterpretCommand";
	}

private:
	std::shared_ptr<IMessagable>				massagable;

};

#endif /* _INTERPRET_COMMAND_H_ */
