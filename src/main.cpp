#include "src/QueueCommand.h"
#include "src/ExceptionHendler.h"

#include "BootStrapHendler.h"

#include "src/main.h"

int mainCommand()
{
	BootStrapHandler boostStrap;
	ExceptionHendler excHendler;

	while(true)
	{
		QueueCommand q(100);
		boostStrap.LoadSetting(excHendler, q);
		auto comCur = q.GetCurrentCommand();
		try
		{
			if (comCur)
				comCur->Execute();
			else
				return 0;
		}
		catch(const std::exception &c)
		{
			excHendler.Handle(comCur, c)->Execute();
		}
	}
}