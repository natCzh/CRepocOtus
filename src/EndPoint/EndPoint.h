#ifndef _END_POINT_H_
#define _END_POINT_H_

#include "EndPoint/IEndPoint.h"
#include "EndPoint/InterpretCommand.h"
#include "EndPoint/MessageAdapter.h"
#include "EndPoint/Message.h"


// ���������� ������������������� ������� InterpretCommand

// ����� �� ������� ��������� ������, ������������ � json -> string -> IMessage -> InterpretCommand
class EndPoint: public IEndPoint
{
public:
	EndPoint(ICommand_Ptr initCommand)
	{
		initCommand->Execute();
	}
	
	void process()
	{
		// �������� ������
		//�� json -> string
		// string -> IMessage
		// TODO ����������� interpretCommand ��������� ������ ��� ������ 
		Message m;
		InterpretCommand interpretCommand(std::make_shared<Message>(m));
		interpretCommand.Execute();

	}


private:

};

#endif /* _END_POINT_H_ */
