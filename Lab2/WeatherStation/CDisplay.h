#pragma once
#include "IObserver.h"
#include <iostream>
#include "SWeatherInfo.h"

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data) override;
};