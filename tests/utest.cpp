#include "gtest/gtest.h"
#include "IoC/IoC.h"

int main(int argc, char** argv)
{
	//::testing::FLAGS_gtest_filter = "TestIoCScopes*";
	::testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
