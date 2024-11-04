#ifndef _I_O_C_H_
#define _I_O_C_H_

#include <cstring>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "src/Command/ICommand.h"
#include "src/Scopes/Scope.h"
#include "src/Exception/IoCException.h"

//////////////////удалить
#include "EndPoint/MessageAdapter.h"

struct inputParamsIocRegister
{
	std::string							strCommand;
	ICommand_Ptr						command;
};

namespace Scopes
{ class IDependencyResolve; }

class CommandEmpty: public ICommand
{
public:

	virtual ~CommandEmpty() {}

	void Execute() {}

	std::string GetType() { return "CommandEmpty"; }
};

// уже разрешенные команды в IoC
// IoC.Register, Scopes.New, Scopes.Current, Scopes.Delete
// TODO пока класс реализован так
/////////////// список IoC команд
// Скоупы
// "Scopes.GetListIds" - получим вектор пар <ид игрового объектаб ID существующих Scopes>

// Получение объекта, данных
// "GameItems"
// "Game.Queue"

// Команды
// c параметрами
// "CommandInterpret_StartMove" - <ICommand_Ptr>("massagable->getTypeCommand()", massagable) - CommandInterpretCommand_StopMove, CommandInterpretCommand_StartMove
// "CommandInterpret.PrepareForMove" - <ICommand_Ptr>("CommandInterpret.PrepareForMove", std::shared_ptr<UObject>, std::shared_ptr<std::map<std::string, boost::any> > )
// "CommandInterpret.PrepareForStopMove" - <ICommand_Ptr>("CommandInterpret.PrepareForStopMove", std::shared_ptr<UObject>) 

// без параметров
// "Move" - Move - составная команда
// "MoveStop" - берем командy "Move", делаем инжект пустоф команды
// 
class IoC
{
public:


	template<typename T, typename... Args>
	T Resolve(std::string key, Args... args)
	{
		if constexpr (std::is_same_v<ICommand_Ptr, std::shared_ptr<UObject>,  std::shared_ptr<std::map<std::string, boost::any> > >)
		{
			// TODO реализовать
			return nullptr;
		}


	}

	template<typename T, typename Z>
	T Resolve(std::string key, Z args)
	{
		if constexpr (std::is_same_v<ICommand_Ptr,  boost::any>)
		{		
			/*if (strcmp(key.c_str(), "IoC.Register") == 0)
			{
				Register(args);
				return std::shared_ptr<CommandEmpty>(new CommandEmpty);
			}
			else if (strcmp(key.c_str(), "Scopes.New") == 0 || strcmp(key.c_str(), "Scopes.Current") == 0 || strcmp(key.c_str(), "Scopes.Delete") == 0)
			{
				ScopesProcessing(key, args);
				return std::shared_ptr<CommandEmpty>(new CommandEmpty);
			}
			else
				return ResolveCommand(key, args);*/

			return std::shared_ptr<CommandEmpty>(new CommandEmpty);
		}
		else if constexpr (std::is_same_v<ICommand_Ptr, std::shared_ptr<MessageAdapter> >)
		{
			// тут ¤то-то произойдет
			return std::shared_ptr<CommandEmpty>(new CommandEmpty);
		}




		if (strcmp(key.c_str(), "IoC.Register") == 0)
		{
			Register(args);
			return std::shared_ptr<CommandEmpty>(new CommandEmpty);
		}
		else if (strcmp(key.c_str(), "Scopes.New") == 0 || strcmp(key.c_str(), "Scopes.Current") == 0 || strcmp(key.c_str(), "Scopes.Delete") == 0) // "Scopes.GetListIds" - 
		{
			ScopesProcessing(key, args);
			return std::shared_ptr<CommandEmpty>(new CommandEmpty);
		}
		else
			return ResolveCommand(key, args);
	}

	template<typename T>
	T Resolve(std::string key)
	{
		/*if constexpr (std::is_same_v<std::shared_ptr<UObject>>)
		{
			// надо вернуть объект в текущем скоупе
			// првоерить что пришло "GameItems"
			std::shared_ptr<UObject> curObj_ptr = std::make_shared<StateShip>(new StateShip());
			return curObj_ptr;
			// ioc.Resolve<std::shared_ptr<UObject> >("GameItems") вот такое обращение
		}
		elseif constexpr (std::is_same_v<std::shared_ptr<QueueCommand> >)
		{
			// надо вернуть объект в текущем скоупе
			// првоерить что пришло "Game.Queue"
			std::shared_ptr<QueueCommand> queue = std::make_shared<QueueCommand>(new QueueCommand(100));
			return queue;
			// ioc.Resolve<std::shared_ptr<QueueCommand> >("Game.Queue") вот такое обращение
		}*/

		// тут мы просто берем из текущего скоупа то что нам нужно
		auto result = currentScope->GetValueOrDefault(key);
		if (result == nullptr)
			throw IoCException("IoC parameter of key isn't exist");
		
		return <T>(result);
	}

protected:

	ICommand_Ptr ResolveCommand(const std::string &key, void *args);

	void Register(void *args);

	void CreateScope(size_t idScope);
	void SetCurrentScope(size_t idScope);
	void DeleteScope(size_t idScope);

	void ScopesProcessing(std::string key, void *args);

	std::unordered_map<int, std::shared_ptr<Scopes::Scope> >					scopes; // помен¤ться на boost !!!!!!!!!
	std::shared_ptr<Scopes::Scope>												currentScope;

	std::mutex																	mutex;
};

#endif /* _I_O_C_H_ */