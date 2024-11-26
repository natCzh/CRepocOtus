#ifndef _INIT_GAME_CLASS_COMMON_H_
#define _INIT_GAME_CLASS_COMMON_H_

#include <string>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Command/ICommand.h"
#include "Exception/MessageTourneySException.h"
#include "IoC/IoC.h"
#include "CommonLib/UObject.h"
#include "Common/SpaceShip.h"

extern IoC* ioc;
// у класса хранится файл, где прописаны соответсвия типу объекта его характеристики
// тут мы заполним "DescriptionMove" и загрузим нужные плагины
class InitGameClassCommon: public ICommand
{
public:

    InitGameClassCommon(std::vector<unsigned long long> idObjs_, size_t idScope_)
        : idObjs(idObjs_)
        , idScope(idScope_)
    {}

    virtual ~InitGameClassCommon(){}

    void Execute() override
    {
        ioc->Resolve<void>("Scopes.Current.SetId", idScope);

        for (auto iter = idObjs.begin(); iter != idObjs.end(); iter++)
            objVect[*iter] = std::make_shared<SpaceShip>();
        ioc->Resolve<ICommand_Ptr, std::string, std::unordered_map<unsigned long long, UObject_Ptr> >("IoC.Register", "GameItems", objVect)->Execute();

        std::vector<std::string> vectStr;
        vectStr.push_back("");
        for (auto iter = idObjs.begin(); iter != idObjs.end(); iter++)
            descMovement[*iter] = std::vector<std::string>(vectStr);
        ioc->Resolve<ICommand_Ptr, std::string, std::unordered_map<unsigned long long, std::vector<std::string> > >("IoC.Register", "Description.Movement", descMovement)->Execute();

        vectStr.push_back("");
        for (auto iter = idObjs.begin(); iter != idObjs.end(); iter++)
            listPluginsObg[*iter] = std::vector<std::string>(vectStr);
        ioc->Resolve<ICommand_Ptr, std::string, std::unordered_map<unsigned long long, std::vector<std::string> > >("IoC.Register", "GameItems.listPlugins", listPluginsObg)->Execute();
    }

    std::string GetType() override
    {
        return "InitGameClassCommon";
    }

private:
    std::vector<unsigned long long>                                                             idObjs;
    size_t                                                                                      idScope;
    std::unordered_map<unsigned long long, UObject_Ptr>                                         objVect;
    std::unordered_map<unsigned long long, std::vector<std::string>>         descMovement;
    std::unordered_map<unsigned long long, std::vector<std::string> >         listPluginsObg;
};

#endif /* _INIT_GAME_CLASS_COMMON_H_ */
