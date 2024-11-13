#ifndef _REGISTER_COMMAND_H_
#define _REGISTER_COMMAND_H_

#include <vector>
#include <string>

#include "Command/ICommand.h"
#include "Command/SimpleMacroCommand.h"
//#include "Command/MoveCommand.h"
#include "Command/CommandCommonMove.h"
#include "IoC/IoC.h"

// тут мы опишем, что значит команда Move для игры
// читаем json и парсим в строку // TODO !!!!!!!!!!!!!!!!!!!!!!

// CheckFuelComamnd
// MoveCommand
// BurnFuelComamnd



// перепроверить точно ли все так !!!!!!!!!!!!!!!!
class RegisterMove
{
public:
	static void process()
	{
/*		//  ioc.Resolve<ICommand_Ptr>("IoC.Register"
		std::vector<std::string>						vectCommandMove;
		std::vector<std::shared_ptr<ICommand> > cmds_value;
		unsigned int sizeVect = vectCommandMove.size();
		for (unsigned int it = 0; it < sizeVect; it++)
		{
			ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>(vectCommandMove[it]);
			cmds_value.push_back(cmd);
        }*/
	}


};

#endif /* _REGISTER_COMMAND_H_ */
