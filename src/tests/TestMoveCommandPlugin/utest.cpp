#include <thread>
#include "gtest/gtest.h"
#include "gtestparamparser.h"
UserParams userparams;
int main(int argc, char** argv)
{
	// ::testing::FLAGS_gtest_filter = "TestInterfaceOverflow_InputSignals*";
	//::testing::FLAGS_gtest_repeat = 10000;
	userparams.setParams(argc,argv);
	::testing::InitGoogleTest (&argc, argv);
	return RUN_ALL_TESTS();
}
