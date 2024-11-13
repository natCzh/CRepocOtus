#ifndef _I_PLUGIN_H_
#define _I_PLUGIN_H_

#include <string>
#include <memory>

#include <QtPlugin>

#include "IoC/IoC.h"
#include "IPluginExport.h"

class IPlugin
{
public: 

	virtual ~IPlugin() {};

	// virtual void InitPlugin(IoC* iocCur) = 0;
	virtual void Load() = 0;
	virtual std::string GetType() = 0;
};

#define IPlugin_iid "Qt.PlugAndPaint.IPlugin"
Q_DECLARE_INTERFACE(IPlugin, IPlugin_iid)

#endif /* _I_PLUGIN_H_ */
