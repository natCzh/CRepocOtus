#ifndef _MOVE_COMMAND_PLUGIN_H_
#define _MOVE_COMMAND_PLUGIN_H_

#include <string>
#include <QtPlugin>
#include <QObject>

#include "../../CommonLib/IPlugin.h"
#include "../../CommonLib/UObject.h"
#include "IoC.h"


// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!
// "IMovable.Location" - 


// "IMovable.Location.Set" - 

// "IMovable.Velocity"
// "Command.Move"


class MoveCommandPlugin: public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID IPlugin_iid)
    Q_INTERFACES(IPlugin)

public:

	void Load() override;

	void InitPlugin(std::shared_ptr<IoC> iocCur);

	std::string GetType() override;
private:
	//std::shared_ptr<IoC> ioc_;
};

#endif /* _MOVE_COMMAND_PLUGIN_H_ */
