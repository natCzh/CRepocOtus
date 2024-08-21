#ifndef _COMAAND_H
#define _COMAAND_H

#include <memory>
#include <list>

#include "ICommand.h"
#include "Fuel.h"
#include "CommandException.h"

class CheckFuelComamnd : public ICommand
{
public:
	CheckFuelComamnd(std::shared_ptr<Fuel> &fuelValue, int countDistValue)
		: fuelCur(fuelValue)
		, countDistance(countDistValue)
	{}

	void Execute() override
	{
		int res = fuelCur->getAmountFuel() - countDistance * fuelCur->getConsumptionUnit();
		if (res < 0)
			throw CommandException("Error in CheckFuelComamnd");
	}

	std::string GetType() override
	{
		return "CheckFuelComamnd";
	}

public:
	std::shared_ptr<Fuel>		fuelCur;		// сущность с топливом
	int							countDistance;	// дистанция на которую надо проверить топливо и сместить потом
};

class BurnFuelComamnd : public ICommand
{
public:
	BurnFuelComamnd(std::shared_ptr<Fuel> &fuelValue, int countDistValue)
		: fuelCur(fuelValue)
		, countDistance(countDistValue)
	{}

	void Execute() override
	{
		int res = fuelCur->getAmountFuel() - countDistance * fuelCur->getConsumptionUnit();
		fuelCur->setAmountFuel(res);
	}

	std::string GetType() override
	{
		return "BurnFuelComamnd";
	}

public:
	std::shared_ptr<Fuel>		fuelCur;		// сущность с топливом
	int							countDistance;	// дистанция на которую надо проверить топливо и сместить потом
};

class SimpleMacroCommand : public ICommand
{
public:
	SimpleMacroCommand(const std::shared_ptr<std::vector<ICommand> > cmds_value)
		: cmds(cmds_value)
	{}

	void Execute()
	{
		unsigned int sizeData = cmds->size();
		for (unsigned int it = 0; it < sizeData; it++)
			cmds->at(it).Execute();
	}

private:
	std::shared_ptr<std::vector<ICommand> > cmds;
};

#endif /* _COMAAND_H */