#pragma once

#include "CBeverage.h"

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake()
		: CBeverage("Milkshake")
	{
	}

	double GetCost() const override
	{
		return 80;
	}
};
