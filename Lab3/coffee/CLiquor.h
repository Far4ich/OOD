#pragma once

#include "CCondimentDecorator.h"

// ��� ������
enum class LiquorType
{
	Chocolate, // ����������
	Walnut, // �������� 
};

// ������� "�����"
class CLiquor : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr&& beverage, LiquorType liquorType)
		: CCondimentDecorator(move(beverage))
		, m_liquorType(liquorType)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 50;
	}
	std::string GetCondimentDescription() const override
	{
		return std::string(m_liquorType == LiquorType::Chocolate ? "Chocolate" : "Walnut")
			+ " liquor";
	}

private:
	LiquorType m_liquorType;
};