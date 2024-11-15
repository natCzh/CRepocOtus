#ifndef _MOVE_COMMAND_PLUGIN_H_
#define _MOVE_COMMAND_PLUGIN_H_

#include <string>
#include <QtPlugin>
#include <QObject>

#include "../../CommonLib/IPlugin.h"
#include "../../CommonLib/UObject.h"
#include "ClassFunctionMove.h"
#include "IoC/IoC.h"


// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!
// "IMovable.Location" - 


// "IMovable.Location.Set" - 

// "IMovable.Velocity"
// "Command.Move"


class MoveCommandPlugin: public QObject, public IPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID IPlugin_iid)
    Q_INTERFACES(IPlugin)

public:

    ~MoveCommandPlugin()
    {}

    void Load() override;

    void InitPlugin(IoC* iocCur) override;

	std::string GetType() override;
private:
    ClassFunctionMove                   classFunctionMove;
};

#endif /* _MOVE_COMMAND_PLUGIN_H_ */
