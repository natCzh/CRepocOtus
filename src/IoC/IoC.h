#ifndef _I_O_C_H_
#define _I_O_C_H_

#include "scopes/IDependencyResolve.h"
#include "scopes/DependencyResolve.h"

// уже разрешенные команды в IoC
// IoC.Register, Scopes.Create.Empty, Scopes.Create.Root,  Scopes.Current, Scopes.Delete(по ид), Scopes.Current.Set, Scopes.Current.SetId(по ид), Scopes.Current.Clear



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

	IoC()
		: dependencyResolve(std::make_shared<Scopes::DependencyResolve>())
	{}

	template<typename T, typename TFunc, typename... Args>
	T Resolve(std::string key, Args... args)
	{
		return (T) dependencyResolve->Resolve<T, TFunc, Args...>(key, args...);
	}

	template<typename T, typename... Args>
	T Resolve(std::string key, Args... args)
	{
		return (T) dependencyResolve->Resolve<T, Args...>(key, args...);
	}

protected:

	std::shared_ptr<Scopes::DependencyResolve>						dependencyResolve;
};

#endif /* _I_O_C_H_ */