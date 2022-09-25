#pragma once
#include "IObserver.h"
#include "SWeatherInfo.h"
#include "SStatsParameters.h"
#include <iostream>

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override
	{
		UpdateStats(m_temeratureStats, data.temperature);
		UpdateStats(m_humidityStats, data.humidity);
		UpdateStats(m_pressureStats, data.pressure);

		PrintStats(m_temeratureStats, "Temp");
		PrintStats(m_humidityStats, "Hum");
		PrintStats(m_pressureStats, "Pressure");

		std::cout << "----------------" << std::endl;
	}

	void UpdateStats(SStatsParameters& stats, double value)
	{
		if (stats.min > value)
		{
			stats.min = value;
		}
		if (stats.max < value)
		{
			stats.max = value;
		}
		stats.acc += value;
		++stats.countAcc;
	}

	void PrintStats(SStatsParameters& stats, std::string toString)
	{
		std::cout << "Max " << toString << " " << stats.max << std::endl;
		std::cout << "Min " << toString << " " << stats.min << std::endl;
		std::cout << "Average " << toString << " " << (stats.acc / stats.countAcc) << std::endl;
	}

	SStatsParameters m_temeratureStats;
	SStatsParameters m_humidityStats;
	SStatsParameters m_pressureStats;
};