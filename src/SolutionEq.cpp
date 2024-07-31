#include <math.h>

#include "SolutionEq.h"

std::vector<double> SolutionEq::solve(double a, double b, double c)
{
	if (a != a || isinf(a) || b != b || isinf(b) || c != c || isinf(c))
		throw "Error - coeffiсient isn't correct";

	std::vector<double> result;

	double eps = 10e-3;
	if (std::abs(a) < eps)
		throw "Error - a = 0";

	double D = b * b - 4 * a * c;
	if (D > eps)
	{
		double res = (-b + std::sqrt(D)) / (2 * a);
		result.push_back(res);
		res = (-b - std::sqrt(D)) / (2 * a);
		result.push_back(res);
		return result;
	}
	if (D < 0)
		return result;
	double res = (-b) / (2 * a);
	result.push_back(res);
	result.push_back(res);
	return result;
}