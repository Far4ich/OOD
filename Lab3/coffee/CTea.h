#pragma once

#include "CBeverage.h"

// ×àé
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea")
		: CBeverage(description)
	{
	}

	double GetCost() const override
	{
		return 30;
	}
};