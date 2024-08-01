#include <limits>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../src/SolutionEq.h"

using namespace testing;

class TestSolutionEq : public Test 
{

public:
	TestSolutionEq() 
	{}

    virtual ~TestSolutionEq(){}
};

TEST (TestSolutionEq, test3)
{
	double a = 1.0;
	double b = 0.0;
	double c = 1.0;
	std::vector<double> result;
	result = SolutionEq::solve(a, b, c);

	EXPECT_TRUE(result.empty());
}

TEST (TestSolutionEq, test5)
{
	double a = 1.0;
	double b = 0.0;
	double c = -1.0;
	std::vector<double> result = SolutionEq::solve(a, b, c);

	EXPECT_NEAR(result[0], 1, 1e-1);
	EXPECT_NEAR(result[1], -1, 1e-1);
}

TEST (TestSolutionEq, test7)
{
	double a = 1.0;
	double b = 2.0;
	double c = 1.0;
	std::vector<double> result = SolutionEq::solve(a, b, c);

	EXPECT_NEAR(result[0], -1, 1e-1);
	EXPECT_NEAR(result[1], -1, 1e-1);
}

TEST (TestSolutionEq, test9)
{
	double a = 0.0;
	double b = 2.0;
	double c = 1.0;
	std::vector<double> result;
	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);
}

TEST (TestSolutionEq, test11)
{
	double a = 1.0;
	double b = 2.00002;
	double c = 1.0;

	std::vector<double> result = SolutionEq::solve(a, b, c);

	EXPECT_NEAR(result[0], -1, 1e-1);
	EXPECT_NEAR(result[1], -1, 1e-1);
}

TEST (TestSolutionEq, test13)
{
	// 1 a - infinity
	double a = std::numeric_limits <double>::infinity();
	double b = 2.0;
	double c = 1.0;

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 2 a - -infinity
	a = -std::numeric_limits <double>::infinity();
	b = 2.0;
	c = 1.0;

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 3 a - NaN
	a = std::numeric_limits<double>::quiet_NaN();
	b = 2.0;
	c = 1.0;

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 4 b - infinity
	a = 1.0;
	b = std::numeric_limits <double>::infinity();
	c = 1.0;

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 5 b - -infinity
	a = 1.0;
	b = -std::numeric_limits <double>::infinity();
	c = 1.0;

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 6 b - NaN
	a = 1.0;
	b = std::numeric_limits<double>::quiet_NaN();
	c = 1.0;

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 7 c - infinity
	a = 1.0;
	b = 2.0;
	c = std::numeric_limits <double>::infinity();

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 8 c - -infinity
	a = 1.0;
	b = 2.0;
	c = -std::numeric_limits <double>::infinity();

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);

	// 9 c - NaN
	a = 1.0;
	b = 2.0;
	c = std::numeric_limits<double>::quiet_NaN();

	EXPECT_THROW(SolutionEq::solve(a, b, c), const char*);
}
