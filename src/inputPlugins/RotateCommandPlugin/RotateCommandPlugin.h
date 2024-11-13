#ifndef _ROTATE_COMMAND_PLUGIN_H_
#define _ROTATE_COMMAND_PLUGIN_H_

#include <string>

#include "Common/IPlugin.h"

// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!
// "IRotable.Direction"
// "IRotable.Direction.Set"
// "Adapters.IRotable"
// "Command.Rotate"

class RotateCommandPlugin: public IPlugin
{
public:

	void Load() override;

	std::string GetType() override;
};

#endif /* _ROTATE_COMMAND_PLUGIN_H_ */
