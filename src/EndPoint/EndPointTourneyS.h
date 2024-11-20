#ifndef _END_POINT_H_
#define _END_POINT_H_

#include "EndPoint/IEndPoint.h"
#include "EndPoint/InterpretCommand.h"
#include "EndPoint/MessageAdapter.h"
#include "EndPoint/Message.h"

// EndPoint отвечает за обработку сообщений извне
// необходимо проинициализировать команды InterpretCommand !!!!!! TODO
class EndPoint: public IEndPoint
{
public:

    EndPoint(ICommand_Ptr initCommand) {}

    // переж этим получили запрос
    //из json -> string
    // string -> IMessage
    /// @brief Создание нужной команды и добавление ее в очередь
    /// @param[in] m - сообщение Message
    /// @param[in] scopeId - скоуп ид уже нужной игры
    /// @param[in] queue - очередь команд уже нужной игры
    void process(UObject_Ptr m, size_t scopeId, std::shared_ptr<QueueCommand> queue)
	{
		std::shared_ptr<IMessagable> messagable = std::make_shared<MessageAdapter>(std::make_shared<Message>(m));
        std::shared_ptr<InterpretCommand> interpretCommand = std::make_shared<InterpretCommand>(std::make_shared<IMessagable>(messagable), scopeId);
		// те interpret Cоmmand мы положим в очередь игры уже для нужного объекта
	}
};

#endif /* _END_POINT_H_ */
