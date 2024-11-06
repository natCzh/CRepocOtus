#ifndef _DEPENDENCY_RESOLVE_H_
#define _DEPENDENCY_RESOLVE_H_

#include <unordered_map>
#include <memory>
#include <mutex>
#include <functional>
#include <boost/lexical_cast.hpp>

#include "scopes/IDependencyResolve.h"
#include "scopes/Scope.h"
#include "Command/ICommand.h"
#include "scopes/CommandsScope/RegisterDependencyCommand.h"

//template<typename T, typename... Args>

namespace Scopes
{
	class DependencyResolve: public IDependencyResolve
	{
	public:

		DependencyResolve();


		template<typename T, typename TFunc, typename... Args>
		T Resolve(std::string key, Args... args)
		{
			if (strcmp(key.c_str(), "IoC.Register") == 0)
			{
				auto items{::std::tie(args...)};
				std::string key1 = static_cast<std::string>(::std::get<0>(items));
				auto func = &(::std::get<1>(items));


				auto&& t = std::forward_as_tuple(args...);
				auto t1 = std::get<1>(items);
				auto t2 = std::get<2>(items);
				decltype(t2) df = 0;
				//auto t2 = decltype(std::function{ t1 })::result_type;
				//using t2 = decltype(std::get<>)
				std::shared_ptr<ICommand> cmdI = std::make_shared<RegisterDependencyCommand<TFunc, decltype(t2)> >(RegisterDependencyCommand<TFunc, decltype(t2)>(this, key1, t1));
				return cmdI;

				/*if constexpr (std::is_same<T, ICommand_Ptr>)
				{
					int sdfsd = 0;
				}
				else
				{
					int sdf = 0;
				}*/

				int swedf = 0;

				//if constexpr (std::is_same_v<ICommand_Ptr, std::function<ICommand_Ptr()> >)
				//if constexpr (std::is_same_v<T, std::function<ICommand_Ptr()> >)
				//{
					//auto list = { Args...};
					//std::function<ICommand_Ptr()> functArgs = boost::lexical_cast<std::function<ICommand_Ptr()> >(args);


					//std::function<ICommand_Ptr()> func = args[0];
					//T v = ResolveInput<T>(key, func);





				//}
			}
			//{
				if (strcmp(key.c_str(), "IoC.Register") == 0)
				{
					//auto res = std::make_shared<T>(RegisterDependencyCommand<T, Args...>(this, key, ...args));
					//ICommand_Ptr cmd = std::make_shared<RegisterDependencyCommand<ICommand_PtrArgs...>(new RegisterDependencyCommand<ICommand_Ptr, Args...>(this, key/*, std::function<ICommand_Ptr//()>*/));
					//return cmd;
					//RegisterDependencyCommand<T> cmd = RegisterDependencyCommand<T>(this, key, args);
					//return cmd;
				}



				//if (strcmp(key.c_str(), "IoC.Register") == 0)
					// TODOD доделать !!!!

			//}
			return nullptr;
		}




		template<typename T>
		T ResolveInput(std::string key, std::function<ICommand_Ptr()> func)
		{
			RegisterDependencyCommand<T> cmd = RegisterDependencyCommand<T>(this, key, func);
			return cmd;
		}


		void Init();

		// работа со скоупами
		void SetCurrentScope(std::shared_ptr<Scopes::Scope> scopeCur_);
		void ClearCurrentScopeCommand();
		std::shared_ptr<Scopes::Scope> GetCurrentScope();
	
		/*ICommand_Ptr Resolve(const std::string &key, UObject *obj)
		{
			// ICommand_Ptr
			return scope.begin()->second;
		}

		void dependencyResolve(std::unordered_map<std::string, ICommand_Ptr> &scopeCur)
		{
			// проверки на родительский скоуп нету
			scope = scopeCur;
		}

		ICommand_Ptr GetValueOrDefault(const std::string &key)
		{
			auto iterF = scope.find(key);
			if (iterF != scope.end())
				return iterF->second;
			else
				return nullptr;
		}
		
		void AddCommand(const std::string &key, ICommand_Ptr command) override
		{
			scope[key] = command;
		}*/





	private:

		static std::shared_ptr<Scopes::Scope>											currentScope;
		static std::unordered_map<int, std::shared_ptr<Scopes::Scope> >					scopes;
		std::mutex																		mutex;
	};
}

#endif /* _DEPENDENCY_RESOLVE_H_ */