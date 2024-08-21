#ifndef _COMAAND_H
#define _COMAAND_H

#include <memory>

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

#endif /* _COMAAND_H */