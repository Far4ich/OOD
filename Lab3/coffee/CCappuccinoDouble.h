#pragma once

#include "CCoffee.h"

// ���������
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