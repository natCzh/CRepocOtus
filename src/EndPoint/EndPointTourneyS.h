#ifndef _END_POINT_H_
#define _END_POINT_H_

#include "EndPoint/IEndPoint.h"
#include "EndPoint/InterpretCommand.h"
#include "EndPoint/MessageAdapter.h"
#include "EndPoint/Message.h" // TODO перепроверить подключения !поудалять !!!!!!!!!!
#include "src/Common/ThreadDeque.h"
#include "service/TourneyService/EventLoop.h"
#include "Exception/MessageTourneySException.h"

// EndPoint отвечает за прием сообщений извне

// необходимо проинициализировать команды InterpretCommand

// Класс то образом принимает запрос, конвертирует в json -> string -> IMessage -> InterpretCommand
class EndPoint: public IEndPoint
{
public:
	// TODO очередь нужно передавать тоже через IOC пока сделаем так через конструктор
	EndPoint(ICommand_Ptr initCommand, std::shared_ptr<std::map<size_t, EventLoop> > collectionGame_)
		: collectionGame(collectionGame_)
	{
		initCommand->Execute();
	}
	
	void process()
	{
		// получили запрос
		//из json -> string
		// string -> IMessage
		// TODO пеоределать interpretCommand создается всегда при вызове 
		Message m;

		/////////////////////////////////////////////////////////////
		std::shared_ptr<IMessagable> messagable = std::make_shared<MessageAdapter>(std::make_shared<Message>(m));
		// найдем в коллекции игр нужную команду
		auto curGame = std::find(collectionGame->begin(), collectionGame->end(), messagable->getIdGame()); // TODO !!!! потом тут сделать проверку и доставить игру не по ид, а по хэшу, сделать паттерн корелейшен ид
		if (curGame == collectionGame->end())
			throw MessageTourneySException("Message failed - id of game isn't correct");
		auto indexGame = curGame->second.findIndexCollectionGameId(messagable->getIdObject());
		size_t scopeIdCur_ = getScopeIdCur();

		std::shared_ptr<InterpretCommand> interpretCommand = std::make_shared<InterpretCommand>(std::make_shared<IMessagable>(messagable), scopeIdCur_); // это мы потом запихиваем в очередь eventloop



		// те interpret Cоmmand мы положим в очередь игры уже для нужного объекта
	}

	size_t getScopeIdCur()
	{
		size_t scopeIdCur_ = 0; // TODO - это надо как-то вычислять !!!!!!
		return scopeIdCur_;
	}

private:

	std::shared_ptr<std::map<size_t, EventLoop> > collectionGame; // ссылка на очередь игр

};

#endif /* _END_POINT_H_ */
