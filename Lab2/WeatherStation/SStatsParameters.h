#pragma once
#include <climits>
#include <algorithm>

struct SStatsParameters
{
	double min = std::numeric_limits<double>::infinity();
	double max = -std::numeric_limits<double>::infinity();
	double acc = 0;
	unsigned countAcc = 0;
};