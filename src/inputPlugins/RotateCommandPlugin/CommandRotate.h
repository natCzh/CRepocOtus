#ifndef _COMMAND_ROTATE_H_
#define _COMMAND_ROTATE_H_

#include <QDebug>

#include "../../Command/ICommand.h"
#include "../../CommonLib/objectAble/IRotable.h"

class CommandRotate: public ICommand
{
public:
	CommandRotate(std::shared_ptr<IRotable> obj_)
		: obj(obj_) 
	{}
	
	void Execute() override
	{
		int d = boost::any_cast<int>(obj->getDirecton());
		int dNew = boost::any_cast<int>(obj->getDirectonAngular());
		int n = boost::any_cast<int>(obj->getDirectonNumber());

		int newD = std::fmod(d + dNew, n);
		if (newD < 0)
			newD += n;

		boost::any newValueAny = newD;
		obj->setDirection(newValueAny);

        qDebug() << QString::fromStdString(GetType()) << " Direct old - " << d << ", direct new - " << newD;
	}

	std::string GetType() override
	{
		return "CommandRotate";
	}
	
protected:

	std::shared_ptr<IRotable>			obj;
};

#endif /* _COMMAND_ROTATE_H_ */
