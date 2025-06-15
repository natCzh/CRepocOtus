#ifndef _PARSE_JSON_COMMAND_H_
#define _PARSE_JSON_COMMAND_H_

#include "Command/ICommand.h"

#include "Base/jsoncpp/jsonutils.h"
#include "Base/jsoncpp/utils.h"
#include "Common/BaseTypeJson.h"

class ParseJsonCommand : public ICommand
{
public:
	ParseJsonCommand(const std::string &nameCommand_, const std::string &filenameConfig_, size_t idScope_)
		: nameCommand(nameCommand_)
		, filenameConfig(filenameConfig_)
		, idScope(idScope_)
	{}

	void Execute()
	{
		//Json::Value root;
		//bool rez = jsonCommon::FillJsonRoot(filenameConfig, root);
		//commonJson::js_array<std::string> configCur;
		//configCur.read(root);

		int sdf = 0; 
		
	}

	std::string GetType()
	{
		return "ParseJsonCommand";
	}

protected:
	
	std::string											nameCommand;
	std::string											filenameConfig;
	size_t												idScope;
};

#endif /* _PARSE_JSON_COMMAND_H_ */