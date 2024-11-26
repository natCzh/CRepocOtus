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
                std::unordered_map<unsigned long long, std::shared_ptr<std::vector<std::string> > > vectExistParamMap;
                vectExistParam.push_back(vectExistParamMap);

                std::vector<std::string> valueProp;
                auto namePropJson = iterPr->first;
                auto valuePropJson = iterPr->second;
                auto valuePropArray = valuePropJson.toJsonArray();

                for (auto iterStr = valuePropArray.begin(); iterStr != valuePropArray.end(); iterStr++)
                {
                    auto p = iterStr->toString();
                    valueProp.push_back(p.toStdString());
                }

                strNamePr = iterPr->first.toStdString();
                vectExistParam.back() = ioc->Resolve<std::unordered_map<unsigned long long, std::shared_ptr< std::vector<std::string> > > >(strNamePr);
                vectExistParam.back()[idObj] = std::make_shared<std::vector<std::string> >(valueProp);
                ioc->Resolve<ICommand_Ptr, std::string, std::unordered_map<unsigned long long, std::shared_ptr<std::vector<std::string> > > >("IoC.Register", strNamePr, vectExistParam.back())->Execute();
            }
        }
    }
}
