#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "../src/Command.h"

using namespace testing;

TEST(TestFuelCommand, testCheckFuelCommand)
{
	// кол-во топлива хватает
	std::shared_ptr<Fuel> fuelValue(std::make_shared<Fuel>());
	fuelValue->setAmountFuel(6);
	fuelValue->setConsumptionUnit(1);
	int countDistValue = 4;
	CheckFuelComamnd checkFuel(fuelValue, countDistValue);
	EXPECT_NO_THROW(checkFuel.Execute());

	// кол-во топлива ровно
	countDistValue = 6;
	CheckFuelComamnd checkFuel2(fuelValue, countDistValue);
	EXPECT_NO_THROW(checkFuel2.Execute());

	// кол-во топлива не хватает
	countDistValue = 8;
	CheckFuelComamnd checkFuel3(fuelValue, countDistValue);
	EXPECT_THROW(checkFuel3.Execute(), CommandException);
}

TEST(TestFuelCommand, testBurnFuelCommand)
{
	std::shared_ptr<Fuel> fuelValue(std::make_shared<Fuel>());
	fuelValue->setAmountFuel(6);
	fuelValue->setConsumptionUnit(1);
	int countDistValue = 4;
	BurnFuelComamnd burnFuel(fuelValue, countDistValue);
	burnFuel.Execute();
	EXPECT_EQ(fuelValue->getAmountFuel(), 2);
}