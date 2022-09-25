#pragma once

#include "CCoffee.h"

// Латте
class CLatteDouble : public CCoffee
{
public:
	CLatteDouble()
		: CCoffee("Double latte")
	{
	}

	double GetCost() const override
	{
		return 130;
	}
};