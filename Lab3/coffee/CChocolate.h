#pragma once

#include "CCondimentDecorator.h"
#include <cassert>

// Шоколадные дольки
class CChocolate : public CCondimentDecorator
{
public:
	CChocolate(IBeveragePtr&& beverage, unsigned count)
		: CCondimentDecorator(move(beverage))
		, m_sliceCount(count)
	{
		assert(m_sliceCount <= 5 && m_sliceCount > 0);
	}

	double GetCondimentCost() const override
	{
		return 10.0 * m_sliceCount;
	}

	std::string GetCondimentDescription() const override
	{
		return "Chocolate slice x " + std::to_string(m_sliceCount);
	}

private:
	unsigned m_sliceCount;
};