#ifndef _INIT_OBJECT_GAME_H_
#define _INIT_OBJECT_GAME_H_

#include <string>

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Command/ICommand.h"
#include "Exception/MessageTourneySException.h"


// у класса хранится файл, где прописаны соответсвия типу объекта его характеристики
// тут мы заполним "DescriptionMove" и загрузим нужные плагины
class InitObjectGame: public ICommand
{
public:

    InitObjectGame(const std::string &fileName_, unsigned long long idObjType_, unsigned long long idObj_, size_t idScope_)
        : fileName(fileName_)
        , idObjType(idObjType_)
        , idObj(idObj_)
        , idScope(idScope_)
    {}

    virtual ~InitObjectGame(){}

    void Execute() override;

    std::string GetType() override
    {
        return "InitGameClass";
    }

protected:


private:
    std::string                                                                                       fileName;
    unsigned long long                                                                                idObjType;
    unsigned long long                                                                                idObj;
    size_t                                                                                            idScope;
    std::vector< std::unordered_map<unsigned long long, std::shared_ptr<std::vector<std::string> > > >vectExistParam;
};

#endif /* _INIT_OBJECT_GAME_H_ */
