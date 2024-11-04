#ifndef _ROTATE_COMMAND_H_
#define _ROTATE_COMMAND_H_

#include "Command/ICommand.h"
#include "Common/UObject.h"
#include "Exception/IoCException.h"

class RotateCommand : public ICommand
{
public:

	RotateCommand(const std::shared_ptr<UObject> &obj)
		: o(obj)
	{}

	// return 0 - ok,
	 // 1 - error
	void Execute()
	{
		int dirCur, angleRotCur;
		boost::any dirCur_any, angleRotCur_any;
		int errorCode = o->getProperty("direction", dirCur_any);
		if (errorCode)
			throw IoCException("UObject - direction isn't exist");
		errorCode = o->getProperty("angleRotate", angleRotCur_any);
		if (errorCode)
			throw IoCException("UObject - angleRotate isn't exist");
		o->setProperty("direction", dirCur + angleRotCur);
	}

private:
	std::shared_ptr<UObject> o;
};

#endif /* _ROTATE_COMMAND_H_ */
