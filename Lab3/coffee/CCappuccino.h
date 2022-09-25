#pragma once

#include "CCoffee.h"

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino()
		: CCoffee("Cappuccino")
	{
	}

	double GetCost() const override
	{
		return 80;
	}
};