#ifndef _COMMAND_SHOT_H_
#define _COMMAND_SHOT_H_

#include <QDebug>

#include "../../Command/ICommand.h"
#include "../../CommonLib/objectAble/IShotable.h"

class CommandShot: public ICommand
{
public:
	CommandShot(std::shared_ptr<IShotable> obj_)
		: obj(obj_) 
	{}
	
	void Execute() override
	{
		obj->setShotAct();

		int d = boost::any_cast<int>(obj->getNumberShot());
		boost::any newValueAny = d-1;
		obj->setNumberShot(newValueAny);

        qDebug() << QString::fromStdString(GetType()) << "numberShot - " << boost::any_cast<int>(newValueAny);
	}

	std::string GetType() override
	{
		return "CommandShot";
	}
	
protected:

	std::shared_ptr<IShotable>			obj;
};

#endif /* _COMMAND_SHOT_H_ */
