#ifndef _COMAAND_H
#define _COMAAND_H

#include <memory>
#include <list>
#include <cmath>

#include "ICommand.h"
#include "Fuel.h"
#include "CommandException.h"
#include "PropertyUnit.h"

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
	SimpleMacroCommand(const std::vector<std::shared_ptr<ICommand> > &cmds_value)
		: cmds(cmds_value)
	{}

	void Execute()
	{
		unsigned int sizeData = cmds.size();
		for (unsigned int it = 0; it < sizeData; it++)
			cmds[it]->Execute();
	}

	std::string GetType() override
	{
		return "SimpleMacroCommand";
	}

private:
	std::vector<std::shared_ptr<ICommand> > cmds;
};

class ChangeVelocityCommand : public ICommand
{
public:
	ChangeVelocityCommand(std::shared_ptr<UObject> &objCur)
		: obj(objCur)
	{}

	void Execute() override
	{
		double pi = 3.14159;

		// TODO 
		int velocityAll, direction;
		int errorCode = obj->getProperty("velocity", velocityAll);
		if (errorCode)
			throw CommandException("Error parameter velocity is not exist");
		errorCode = obj->getProperty("direction", direction);
		if (errorCode)
			throw CommandException("Error parameter direction is not exist");

		int velocityX = velocityAll * std::round(std::sin(direction * pi / 180.0));;
		int velocityY = velocityAll * std::round(std::cos(direction * pi / 180.0));;
		obj->setProperty("velocity_x", velocityX);
		obj->setProperty("velocity_y", velocityY);
	}

	std::string GetType() override
	{
		return "ChangeVelocityCommand";
	}

private:
	std::shared_ptr<UObject>					obj;
};

class RotateCommand: ICommand
{
public:
	RotateCommand(const std::shared_ptr<UObject> &obj)
		: o(obj)
	{}

	void Execute() override
	{
		int dirCur, angleRotCur;
		int errorCode = o->getProperty("direction", dirCur);
		if (errorCode)
			throw CommandException("Error parameter direction is not exist");
		errorCode = o->getProperty("angleRotate", angleRotCur);
		if (errorCode)
			throw CommandException("Error parameter angleRotate is not exist");
		o->setProperty("direction", dirCur + angleRotCur);
	}

	std::string GetType() override
	{
		return "RotateCommand";
	}

private:
	std::shared_ptr<UObject> o;
};

class RotateCommandWithChangeVelocity: ICommand
{
public:
	RotateCommandWithChangeVelocity(const std::shared_ptr<UObject> &obj)
		: o(obj)
	{}

	void Execute()
	{
		RotateCommand cRotate(o);
		cRotate.Execute();

		ChangeVelocityCommand cChangeVel(o);
		cChangeVel.Execute();
	}

	std::string GetType() override
	{
		return "RotateCommandWithChangeVelocity";
	}

private:
	std::shared_ptr<UObject> o;
};


#endif /* _COMAAND_H */