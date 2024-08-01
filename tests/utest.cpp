#include "gtest/gtest.h"

int main(int argc, char** argv)
{
	//::testing::FLAGS_gtest_filter = "TestCheckOverflowProcess*";
	//::testing::FLAGS_gtest_repeat = 10000;
	::testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
