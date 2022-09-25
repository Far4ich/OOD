#pragma once

#include "CCoffee.h"

// Капуччино
class CCappuccinoDouble : public CCoffee
{
public:
	CCappuccinoDouble()
		: CCoffee("Double cappuccino")
	{
	}

	double GetCost() const override
	{
		return 80;
	}
};