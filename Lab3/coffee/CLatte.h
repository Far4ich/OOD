#pragma once

#include "CCoffee.h"

// Латте
class CLatte : public CCoffee
{
public:
	CLatte()
		: CCoffee("Latte")
	{
	}

	double GetCost() const override
	{
		return 90;
	}
};