#ifndef _END_POINT_H_
#define _END_POINT_H_

#include <memory.h>

#include "EndPoint/IEndPoint.h"
#include "EndPoint/InterpretCommand.h"
#include "EndPoint/MessageAdapter.h"
#include "service/Message.h"

// EndPoint отвечает за обработку сообщений извне
// необходимо проинициализировать команды InterpretCommand !!!!!! TODO
class EndPoint: public IEndPoint
{
public:

    EndPoint() {}

    // переж этим получили запрос
    //из json -> string
    // string -> IMessage
    /// @brief Создание нужной команды и добавление ее в очередь
    /// @param[in] m - сообщение Message
    /// @param[in] scopeId - скоуп ид уже нужной игры
    /// @param[in] queue - очередь команд уже нужной игры
    void process(std::shared_ptr<Message> m, size_t scopeId, std::shared_ptr<QueueCommand> queue)
	{
        std::shared_ptr<IMessagable> messagable = std::make_shared<MessageAdapter>(m);
        std::shared_ptr<InterpretCommand> interpretCommand = std::make_shared<InterpretCommand>(messagable, scopeId, queue);
        interpretCommand->Execute();
		// те interpret Cоmmand мы положим в очередь игры уже для нужного объекта
	}
};

#endif /* _END_POINT_H_ */
