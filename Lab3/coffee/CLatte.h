#pragma once

#include "CCoffee.h"

// �����
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