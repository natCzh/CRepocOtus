#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "../src/Command.h"

using namespace testing;

TEST(TestFuelCommand, testCheckFuelCommand)
{
	// кол-во топлива хватает
	Fuel fuelValue;
	fuelValue.setAmountFuel(6);
	fuelValue.setConsumptionUnit(1);
	int countDistValue = 4;
	CheckFuelComamnd checkFuel(std::make_shared<Fuel>(fuelValue), countDistValue);
	EXPECT_NO_THROW(checkFuel.Execute());

	// кол-во топлива ровно
	countDistValue = 6;
	CheckFuelComamnd checkFuel2(std::make_shared<Fuel>(fuelValue), countDistValue);
	EXPECT_NO_THROW(checkFuel2.Execute());

	// кол-во топлива не хватает
	countDistValue = 8;
	CheckFuelComamnd checkFuel3(std::make_shared<Fuel>(fuelValue), countDistValue);
	EXPECT_THROW(checkFuel3.Execute(), std::exception);
	EXPECT_THROW(checkFuel3.Execute(), CommandException);
}