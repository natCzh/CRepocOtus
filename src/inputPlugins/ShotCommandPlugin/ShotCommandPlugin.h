#ifndef _SHOT_COMMAND_PLUGIN_H_
#define _SHOT_COMMAND_PLUGIN_H_s

#include <string>

#include "Common/IPlugin.h"

// Доступные команды 
// TODO !!!!!!!!!!!! описать !!!!!!!!!!!


class ShotCommandPlugin: public IPlugin
{
public:

	void Load() override;

	std::string GetType() override;
};

#endif /* _SHOT_COMMAND_PLUGIN_H_ */
