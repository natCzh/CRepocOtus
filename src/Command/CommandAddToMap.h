#ifndef _COMMAND_ADD_TO_MAP_H_
#define _COMMAND_ADD_TO_MAP_H_

#include <string>
#include <memory>

class CommandAddToMap
{
public:

    CommandAddToMap(){}

	virtual ~ICommand() {}

	virtual void Execute() = 0;

	virtual std::string GetType() = 0;

protected:

};

#endif /* _COMMAND_ADD_TO_MAP_H_ */
