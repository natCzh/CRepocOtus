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
	// кол-во топлива достаточно
	std::shared_ptr<Fuel> fuelValue(std::make_shared<Fuel>());
	fuelValue->setAmountFuel(6);
	fuelValue->setConsumptionUnit(1);
	int countDistValue = 4;
	BurnFuelComamnd burnFuel(fuelValue, countDistValue);
	burnFuel.Execute();
	EXPECT_EQ(fuelValue->getAmountFuel(), 2);

	// кол-ва топлива меньше
	countDistValue = 3;
	BurnFuelComamnd burnFuel2(fuelValue, countDistValue);
	burnFuel2.Execute();
	EXPECT_EQ(fuelValue->getAmountFuel(), -1);
}

class MockMoveCommand: public ICommand
{
public:
	MOCK_METHOD0(Execute, void());
	MOCK_METHOD0(GetType, std::string());
};

TEST(TestFuelCommand, testMacrocommandMoveLine)
{
	// без ошибок
	std::shared_ptr<Fuel> fuelValue(std::make_shared<Fuel>());
	fuelValue->setAmountFuel(6);
	fuelValue->setConsumptionUnit(1);
	int countDistValue = 4;
	std::shared_ptr<ICommand> c1Check = std::make_shared<CheckFuelComamnd>(fuelValue, countDistValue);
	std::shared_ptr<ICommand> c1Move = std::make_shared<MockMoveCommand>();
	std::shared_ptr<ICommand> c1Burn = std::make_shared<BurnFuelComamnd>(fuelValue, countDistValue);
	std::vector<std::shared_ptr<ICommand> > vectC{ c1Check, c1Move, c1Burn };
	std::shared_ptr<ICommand> mcMoveLine = std::make_shared<SimpleMacroCommand>(vectC);

	mcMoveLine->Execute();
	EXPECT_EQ(fuelValue->getAmountFuel(), 2);

	// с ошибкой
	fuelValue->setAmountFuel(6);
	countDistValue = 7;
	std::shared_ptr<ICommand> c1Check2 = std::make_shared<CheckFuelComamnd>(fuelValue, countDistValue);
	std::shared_ptr<ICommand> c1Burn2 = std::make_shared<BurnFuelComamnd>(fuelValue, countDistValue);
	vectC.clear();
	vectC.push_back(c1Check2);
	vectC.push_back(c1Move);
	vectC.push_back(c1Burn2);
	std::shared_ptr<ICommand> mcMoveLine2 = std::make_shared<SimpleMacroCommand>(vectC);

	EXPECT_THROW(mcMoveLine2->Execute(), CommandException);
}

TEST(TestFuelCommand, testChangeVelocityCommand)
{
	// угол считается от оси У
	// был поворот на 90
	std::shared_ptr<UObject> objCur = std::make_shared<StateShip>();
	objCur->setProperty("velocity", 2);
	objCur->setProperty("velocity_y", 2);
	objCur->setProperty("velocity_x", 0);
	objCur->setProperty("direction", 90);
	ChangeVelocityCommand changeVel(objCur);
	changeVel.Execute();

	int velocityXCur, velocityYCur;
	objCur->getProperty("velocity_x", velocityXCur);
	EXPECT_EQ(velocityXCur, 2);
	objCur->getProperty("velocity_y", velocityYCur);
	EXPECT_EQ(velocityYCur, 0);

	// угол считается от оси У
	// был поворот на 270, те теперь опять 0
	objCur->setProperty("direction", 0);
	ChangeVelocityCommand changeVel2(objCur);
	changeVel2.Execute();

	objCur->getProperty("velocity_x", velocityXCur);
	EXPECT_EQ(velocityXCur, 0);
	objCur->getProperty("velocity_y", velocityYCur);
	EXPECT_EQ(velocityYCur, 2);
}
