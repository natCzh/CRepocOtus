#ifndef _I_PLUGIN_H_
#define _I_PLUGIN_H_

class IPlugin
{
public: 
	virtual ~IPlugin() {};

	virtual void Load() = 0;
};

#endif _I_PLUGIN_H_
