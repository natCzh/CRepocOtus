#ifndef _I_COMMAND_H_
#define _I_COMMAND_H_

#include <string>
#include <iostream>


class ICommand
{
public:
	virtual void Execute() = 0;

	virtual std::string GetType() = 0;
};

using ICommand_Ptr = std::shared_ptr<ICommand>;

#endif /* _I_COMMAND_H_ */