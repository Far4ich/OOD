#pragma once
#include <map>
#include <set>
#include <functional>
#include "IObservable.h"

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		auto i = m_observersDictoinary.find(priority);
		if (i != m_observersDictoinary.end())
		{
			i->second.insert(&observer);
		}
		else
		{
			m_observersDictoinary.insert(std::pair<int, std::set<ObserverType*>>(priority, { &observer }));
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		auto updatedObservers = m_observersDictoinary;
		auto i = updatedObservers.begin();
		for (; i != updatedObservers.end(); i++)
		{
			for (auto& observer : i->second)
			{
				observer->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto i = m_observersDictoinary.begin();
		for (; i != m_observersDictoinary.end(); i++)
		{
			if (i->second.find(&observer) != i->second.end())
			{
				i->second.erase(&observer);
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	//TODO  multmap
	std::map<int, std::set<ObserverType*>> m_observersDictoinary;
};