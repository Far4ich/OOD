#pragma once

#include "CBeverage.h"

// ���
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