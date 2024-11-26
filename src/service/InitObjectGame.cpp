#include <vector>
#include <unordered_map>


#include "service/InitObjectGame.h"
#include "IoC/IoC.h"

extern IoC* ioc;
void InitObjectGame::Execute()
{
    ioc->Resolve<void>("Scopes.Current.SetId", idScope);

    QString qstr = QString::fromStdString(fileName);
    QFile myFile(qstr);
    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw MessageTourneySException("MessageTourneySException - file with typeObject game isn't exist");
    QString val = myFile.readAll();
    myFile.close();


    QJsonDocument jsonD = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonAllPropert = jsonD.object();
    auto iterAllProp = jsonAllPropert.find("typeObject");
    if (iterAllProp == jsonAllPropert.end())
        throw MessageTourneySException("MessageTourneySException - file with typeObject game isn't correct");
    QJsonArray jsonArrayTypeObj = jsonAllPropert["typeObject"].toArray();

    std::string strNamePr;
    foreach (const QJsonValue & value, jsonArrayTypeObj)
    {
        QJsonObject obj = value.toObject();
        unsigned long long idObjTypeJSon = obj.keys().front().toULongLong();
        if (idObjTypeJSon == idObjType)
        {
            auto val1 = obj.toVariantMap()[obj.keys().front()].toMap();
            for (auto iterPr = val1.keyValueBegin(); iterPr != val1.keyValueEnd(); ++iterPr)
            {
                auto namePropJson = iterPr->first;
                auto valuePropJson = iterPr->second;
                auto valuePropArray = valuePropJson.toJsonArray();

                if (namePropJson == "GameItems.listPlugins")
                {
                    for (auto iterStr = valuePropArray.begin(); iterStr != valuePropArray.end(); iterStr++)
                    {
                        auto p = iterStr->toString();
                        vectListPlugin.push_back(p.toStdString());
                    }
                    vectExistParamListPlug = ioc->Resolve<std::unordered_map<unsigned long long, std::shared_ptr< std::vector<std::string> > > >("GameItems.listPlugins");
                    vectExistParamListPlug[idObj] = std::make_shared<std::vector<std::string> >(vectListPlugin);
                    ioc->Resolve<ICommand_Ptr, std::string, std::unordered_map<unsigned long long, std::shared_ptr<std::vector<std::string> > > >("IoC.Register", "GameItems.listPlugins", vectExistParamListPlug)->Execute();
                }
                else if (namePropJson == "Description.Movement")
                {
                    for (auto iterStr = valuePropArray.begin(); iterStr != valuePropArray.end(); iterStr++)
                    {
                        auto p = iterStr->toString();
                        vectDescMovement.push_back(p.toStdString());
                    }
                    vectExistParamDescMov = ioc->Resolve<std::unordered_map<unsigned long long, std::shared_ptr< std::vector<std::string> > > >("Description.Movement");
                    vectExistParamDescMov[idObj] = std::make_shared<std::vector<std::string> >(vectDescMovement);
                    ioc->Resolve<ICommand_Ptr, std::string, std::unordered_map<unsigned long long, std::shared_ptr<std::vector<std::string> > > >("IoC.Register", "Description.Movement", vectExistParamDescMov)->Execute();
                }
            }
        }
    }
}
