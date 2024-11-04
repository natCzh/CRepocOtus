#ifndef _REGISTER_COMMAND_H_
#define _REGISTER_COMMAND_H_

#include <vector>
#include <string>

#include "IoC/IoCGlobal.h"
#include "Command/ICommand.h"
#include "Command/SimpleMacroCommand.h"
#include "Command/MoveCommand.h"
#include "Command/CommandCommonMove.h"

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
		//  ioc.Resolve<ICommand_Ptr>("IoC.Register"
		std::vector<std::string>						vectCommandMove;
		std::vector<std::shared_ptr<ICommand> > cmds_value;
		unsigned int sizeVect = vectCommandMove.size();
		for (unsigned int it = 0; it < sizeVect; it++)
		{
			ICommand_Ptr cmd = ioc.Resolve<ICommand_Ptr>(vectCommandMove[it]);
			cmds_value.push_back(cmd);
		}


	}


};





class Move : public BridgeCommand
{
public:
	Move(const std::vector<ICommand_Ptr> &vectCommandMove_, const std::shared_ptr<UObject> &obj_, std::shared_ptr<QueueCommand> qCommand_)
		: vectCommandMove(vectCommandMove_)
		, obj(obj_)
		, qCommand(qCommand_)
		// , bridgeRepeat()
		, macroCmd(std::make_shared<SimpleMacroCommand>(vectCommandMove))
	{}

	void Execute()
	{
		// bridgeRepeat = std::make_shared<ICommand>(macroCmd);
		// CommandRepeat commandRepeat(qCommand, std::make_shared<ICommand>(bridgeRepeat));
	}

	std::string GetType()
	{
		return "Move";
	}

	void Inject(ICommand_Ptr injectableCommand)
	{
		// bridgeRepeat->Inject
		// cmd = injectableCommand;
		// здесь нужно заменить репит на пустую команду
	}



protected:
	std::vector<ICommand_Ptr>						vectCommandMove;
	std::shared_ptr<UObject>						obj;
	std::shared_ptr<QueueCommand>					qCommand;
	std::shared_ptr<SimpleMacroCommand>				macroCmd;
	// std::shared_ptr<BridgeCommand>					bridgeRepeat;
	// std::shared_ptr<CommandRepeat>					commandRepeat;
};

#endif /* _REGISTER_COMMAND_H_ */