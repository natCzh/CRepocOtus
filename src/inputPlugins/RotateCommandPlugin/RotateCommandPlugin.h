#ifndef _ROTATE_COMMAND_PLUGIN_H_
#define _ROTATE_COMMAND_PLUGIN_H_

#include <string>
#include <QtPlugin>
#include <QObject>

#include "../../CommonLib/IPlugin.h"
#include "../../CommonLib/UObject.h"
#include "IoC/IoC.h"
#include "ClassFunctionRotate.h"

// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!
// "IRotable.Direction"
// "IRotable.Direction.Set"
// "Adapters.IRotable"
// "Command.Rotate"

class RotateCommandPlugin: public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IPlugin_iid)
    Q_INTERFACES(IPlugin)

public:

    ~RotateCommandPlugin()
    {}

	void Load() override;
    void InitPlugin(IoC* iocCur) override;
	std::string GetType() override;

private:
    ClassFunctionRotate                   classFunctionRotate;
};

#endif /* _ROTATE_COMMAND_PLUGIN_H_ */
