﻿#ifndef _DEPENDENCY_RESOLVE_H_
#define _DEPENDENCY_RESOLVE_H_

#include <unordered_map>
#include <memory>
#include <mutex>
#include <functional>
#include <boost/any.hpp>
#include <iostream>
#include <boost/type_traits/is_convertible.hpp>

#include <typeinfo>

#include "Scopes/IDependencyResolve.h"
#include "Scopes/Scope.h"
#include "../../Command/ICommand.h"
#include "Scopes/CommandsScope/RegisterDependencyCommand.h"

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
				auto items{ ::std::tie(args...) };
				std::string key1 = static_cast<std::string>(::std::get<0>(items));
				auto t1 = std::get<1>(items);

				static constexpr size_t n = sizeof...(Args);
				std::shared_ptr<ICommand> cmdI;
				if constexpr (sizeof...(Args) == 3)
				{
					auto t2 = std::get<2>(items);
                    cmdI = std::make_shared<RegisterDependencyCommand<TFunc, decltype(t2)> >(this, key1, t1);
				}
                if constexpr (sizeof...(Args) == 4)
                {
                    auto t2 = std::get<2>(items);
                    auto t3 = std::get<3>(items);
                    cmdI = std::make_shared<RegisterDependencyCommand<TFunc, decltype(t2), decltype(t3)> >(this, key1, t1);
                }
				else if constexpr (sizeof...(Args) == 2)
                    cmdI = std::make_shared<RegisterDependencyCommand1<TFunc> >(this, key1, t1);
				return cmdI;
			}
			else
			{
				 // TODO тут нужно сделать поиск по родителю
				 boost::any curDepend = currentScope->GetValueOrDefault(key);
				 auto items{ ::std::tie(args...) };
				 static constexpr size_t n = sizeof...(Args);
				 if constexpr (sizeof...(Args) == 1)
				 {
					 auto t1 = std::get<0>(items);
					 std::function<T(decltype(t1) )> df = boost::any_cast<std::function<T(decltype(t1))> >(curDepend);
					 return (T) df(t1);
				 }
				 else if constexpr (sizeof...(Args) == 0)
				 {
					 std::function<T()> df = boost::any_cast<std::function<T()> >(curDepend);
					 return (T) df();
				 }
			}

			return (T)NULL;
		}

		template<typename T, typename F>
		T Resolve(std::string key, F args)
		{
			// TODO тут нужно сделать поиск по родителю
			boost::any curDepend = currentScope->GetValueOrDefault(key);
            std::string typeT{typeid(T).name()};
            std::string typeF{typeid(F).name()};
            // std::cout << "type T is " << typeT << "; type F is " << typeF << std::endl;
                std::function<T(F)> df = boost::any_cast<std::function<T(F)> >(curDepend);
				return (T) df(args);
		}

        template<typename T, typename F, typename F2>
        T Resolve(std::string key, F args, F2 args2)
        {
            if (strcmp(key.c_str(), "IoC.Register") == 0)
            {
                int sdf = 0;
                if constexpr (std::is_same<F, std::string>::value)
                {
                    ICommand_Ptr cmdI = std::make_shared<RegisterDependencyCommand2<F2> >(this, args, args2);
                    return cmdI;
                }
            }

            // TODO тут нужно сделать поиск по родителю
            boost::any curDepend = currentScope->GetValueOrDefault(key);
            std::string typeT{typeid(T).name()};
            std::string typeF{typeid(F).name()};
            std::string typeF2{typeid(F2).name()};
            // std::cout << "type T is " << typeT << "; type F is " << typeF << std::endl;
                std::function<T(F, F2)> df = boost::any_cast<std::function<T(F, F2)> >(curDepend);
                return (T) df(args, args2);
        }

		template<typename T>
		T Resolve(std::string key)
		{
			// TODO тут нужно сделать поиск по родителю
			boost::any curDepend = currentScope->GetValueOrDefault(key);
            std::string typeT{typeid(T).name()};
            //std::cout << "type T is " << typeT << std::endl;

            if (curDepend.type() == typeid(std::function<T()>))
            {
                std::function<T()> df = boost::any_cast<std::function<T()> >(curDepend);
                return (T) df();
            }

            T df = boost::any_cast<T>(curDepend);
            return df;
		}

		void Init(std::shared_ptr<Scopes::Scope> scopeCur);

		// работа со скоупами
		/// "Scopes.Current.Set"
		void SetCurrentScope(std::shared_ptr<Scopes::Scope> scopeCur_);
		/// "Scopes.Current.SetId"
		void SetCurrentScopeId(size_t idScope);
		/// "Scopes.Delete"
		void DeleteScope(int idScope);
		/// "Scopes.Current.Clear"
		void ClearCurrentScopeCommand();
		/// "Scopes.Current"
		std::shared_ptr<Scopes::Scope> GetCurrentScope();
		/// "Scopes.Create.Empty"
		std::shared_ptr<Scopes::Scope> NewScopeEmpty(int idScope);
		/// "Scopes.Create.Root"
		std::shared_ptr<Scopes::Scope> NewScopeRoot(int idScope);

	private:

        std::shared_ptr<Scopes::Scope>                                                  currentScope;
		static std::unordered_map<int, std::shared_ptr<Scopes::Scope> >					scopes;
		std::mutex																		mutex;
	};
}

#endif /* _DEPENDENCY_RESOLVE_H_ */
