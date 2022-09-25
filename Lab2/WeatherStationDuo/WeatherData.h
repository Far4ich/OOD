#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

struct SWeatherInfo
{
	std::string measurePlace;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

struct SStatsParameters
{
	double min = std::numeric_limits<double>::infinity();
	double max = -std::numeric_limits<double>::infinity();
	double acc = 0;
	unsigned countAcc = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Measure Place " << data.measurePlace << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
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

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string measurePlace)
		: m_measurePlace(measurePlace)
	{}

	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}
	// Место откуда брались данные (строка)
	std::string GetMeasurePlace() const
	{
		return m_measurePlace;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.measurePlace = GetMeasurePlace();
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}

private:
	std::string m_measurePlace;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
