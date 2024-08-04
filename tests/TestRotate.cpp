# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include "../src/main.h"

using namespace testing;

class MockRotateCommand : public RotateCommand
{

public:
    MockRotateCommand(const std::shared_ptr<UObject> &obj) : RotateCommand(obj)
	{}

	int Execute()
	{
		return RotateCommand::Execute();
	}
};

class TestRotateCommand : public Test
{
public:
	TestRotateCommand()
	{}
};

TEST_F(TestRotateCommand, test1_1)
{
	// Для объекта, c направлением 0 и поменять направление на 45
	std::shared_ptr<UObject> obj = std::make_shared<StateShip>();

	obj->setProperty("direction", 0);
	obj->setProperty("angleRotate", 45);

	MockRotateCommand test(obj);
	int errorCode = test.Execute();
	ASSERT_EQ(errorCode, 0);
	int pos;
	errorCode = obj->getProperty("direction", pos);
	ASSERT_EQ(errorCode, 0);
	ASSERT_EQ(pos, 45);

	// с 45 на 90
	obj->setProperty("angleRotate", 90);
	errorCode = test.Execute();
	ASSERT_EQ(errorCode, 0);

	errorCode = obj->getProperty("direction", pos);
	ASSERT_EQ(errorCode, 0);
	ASSERT_EQ(pos, 135);
}

TEST_F(TestRotateCommand, test1_2)
{
	// Попытка сдвинуть объект, у которого невозможно прочитать текущий угол, приводит к ошибке
	std::shared_ptr<UObject> obj = std::make_shared<StateShip>();

	int posCur;
	int errorCode = obj->getProperty("direction", posCur);
	ASSERT_EQ(errorCode, 0);

	// Попытка сдвинуть объект, у которого невозможно прочитать значение угол поворота, приводит к ошибке
	int velCur;
	errorCode = obj->getProperty("angleRotate", velCur);
	ASSERT_EQ(errorCode, 0);
}

