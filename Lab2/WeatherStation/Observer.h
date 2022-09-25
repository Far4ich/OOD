#pragma once
#include <map>
#include <set>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, int priority) override
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

		auto i = m_observersDictoinary.begin();
		for (;i != m_observersDictoinary.end(); i++)
		{
			for (auto& observer : i->second)
			{
				observer->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType & observer) override
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
	virtual T GetChangedData()const = 0;

private:
	std::map<int, std::set<ObserverType *>> m_observersDictoinary;
};
