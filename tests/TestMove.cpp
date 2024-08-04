# include "gtest/gtest.h"
# include "gmock/gmock.h"

#include "../src/main.h"

using namespace testing;

class MockMoveCommand : public MoveCommand
{

public:
    MockMoveCommand(const std::shared_ptr<UObject> &obj) : MoveCommand(obj)
	{}

	int Execute()
	{
		return MoveCommand::Execute();
	}
};

class TestMoveCommand : public Test
{
public:
	TestMoveCommand()
	{}
};

TEST_F(TestMoveCommand, test1_1)
{
	// ��� �������, ������������ � ����� (12, 5) � ����������� �� ��������� (-7, 3) �������� ������ ��������� ������� �� (5, 8)
	std::shared_ptr<UObject> obj = std::make_shared<StateShip>();

	obj->setProperty("position_x", 12);
	obj->setProperty("position_y", 5);

	obj->setProperty("velocity_x", -7);
	obj->setProperty("velocity_y", 3);

	MockMoveCommand test(obj);
	int errorCode = test.Execute();
	ASSERT_EQ(errorCode, 0);
	int pos;
	errorCode = obj->getProperty("position_x", pos);
	ASSERT_EQ(errorCode, 0);
	ASSERT_EQ(pos, 5);

	errorCode = obj->getProperty("position_y", pos);
	ASSERT_EQ(errorCode, 0);
	ASSERT_EQ(pos, 8);
}

TEST_F(TestMoveCommand, test1_2)
{
	// ������� �������� ������, � �������� ���������� ��������� ��������� � ������������, �������� � ������
	std::shared_ptr<UObject> obj = std::make_shared<StateShip>();

	int posCur;
	int errorCode = obj->getProperty("position_x", posCur);
	ASSERT_EQ(errorCode, 0);
	errorCode = obj->getProperty("position_y", posCur);
	ASSERT_EQ(errorCode, 0);

	// ������� �������� ������, � �������� ���������� ��������� �������� ���������� ��������, �������� � ������
	int velCur;
	errorCode = obj->getProperty("velocity_x", velCur);
	ASSERT_EQ(errorCode, 0);
	errorCode = obj->getProperty("velocity_y", velCur);
	ASSERT_EQ(errorCode, 0);

	// ������� �������� ������, � �������� ���������� �������� ��������� � ������������, �������� � ������
	errorCode = obj->setProperty("velocity_x", velCur);
	ASSERT_EQ(errorCode, 0);
	errorCode = obj->getProperty("velocity_y", velCur);
	ASSERT_EQ(errorCode, 0);
}

