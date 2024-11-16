#ifndef _SHOT_COMMAND_PLUGIN_H_
#define _SHOT_COMMAND_PLUGIN_H_


#include <string>
#include <QtPlugin>
#include <QObject>

#include "../../CommonLib/IPlugin.h"
#include "../../CommonLib/UObject.h"
#include "IoC/IoC.h"
#include "ClassFunctionShot.h"

// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!


class ShotCommandPlugin: public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IPlugin_iid)
    Q_INTERFACES(IPlugin)

public:
    ~ShotCommandPlugin(){}

	void Load() override;
    void InitPlugin(IoC* iocCur) override;
	std::string GetType() override;

private:
    ClassFunctionShot                   classFunctionShot;
};

#endif /* _SHOT_COMMAND_PLUGIN_H_ */
