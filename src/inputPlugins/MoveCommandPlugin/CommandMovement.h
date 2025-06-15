#ifndef _COMMAND_MOVEMENT_H_
#define _COMMAND_MOVEMENT_H_

#include <vector>
#include <cstring>
#include <QDebug>

#include "../../Command/ICommand.h"
#include "IoC/IoC.h"
#include "CommonLib/UObject.h"
#include "Command/SimpleMacroCommand.h"
#include "CommonLib/objectAble/IMovable.h"
#include "MovableAdapter.h"

extern IoC* ioc;
class CommandMovement: public ICommand
{
public:
    CommandMovement(size_t idObject_)
        : idObject(idObject_)
    {}

    void Execute() override
    {
        commandsDescMap = ioc->Resolve<std::unordered_map<unsigned long long, std::vector<std::string> > >("Description.Movement");
        if (!commandsDescMap.empty())
        {
            std::vector<std::string> commandsDesc = commandsDescMap.find(idObject)->second;

            std::unordered_map<unsigned long long, UObject_Ptr> curVectObject = ioc->Resolve<std::unordered_map<unsigned long long, UObject_Ptr> >(
                "GameItems");
            UObject_Ptr obj = curVectObject.find(idObject)->second;

            std::vector<ICommand_Ptr> cmdsVect;
            for (auto iter = commandsDesc.begin(); iter != commandsDesc.end(); iter++)
            {
                std::string strCur = *iter;
                ICommand_Ptr cmdCur = ioc->Resolve<ICommand_Ptr>(strCur, obj);
                cmdsVect.push_back(cmdCur);
            }

            SimpleMacroCommand cmdMacro(cmdsVect);
            cmdMacro.Execute();
            std::cout << "Movement idObj " << idObject << std::endl;
            //ioc->Resolve<ICommand_Ptr>("Command.SimpleMacroCommand", cmdsVect)->Execute();
            qDebug() << QString::fromStdString(GetType()) << " - x: " << boost::any_cast<int>(obj->getProperty("position_x")) << " - y: " << boost::any_cast<int>(obj->getProperty("position_y"));
        }

    }

    std::string GetType() override
    {
        return "Command.Movement";
    }

private:
    size_t                                      idObject;
    std::unordered_map<unsigned long long, std::vector<std::string> > commandsDescMap;
    std::shared_ptr<IMovable> objMove;
};

#endif /* _COMMAND_MOVEMENT_H_ */
