#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
//TODO Разбить 
struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};
//почему структура
//в структуре все public и структура передается по значению(классы по сслыке)
class DanceWaltz : public IDanceBehavior
{
	void Dance() override
	{
		cout << "I'm dancing waltz" << endl;
	}
};

class DanceMinuet : public IDanceBehavior
{
	void Dance() override
	{
		cout << "I'm dancing minuet" << endl;
	}
};

class DanceNoWay : public IDanceBehavior
{
	void Dance() override {}
};

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flightNumber++;
		cout << "I'm flying with wings!!" << " my flight number is " << m_flightNumber << endl;
	}
private:
	int m_flightNumber = 0;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};

struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};

class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

class Duck
{
/*
Unique_ptr не имеет общего указателя. Его нельзя скопировать в другую unique_ptr,
передать по значению в функцию или использовать в любом алгоритме стандартной библиотеки C++,
который требует создания копий. unique_ptr можно только переместить.
*/
public:
	Duck(unique_ptr<IFlyBehavior>&& flyBehavior,
		unique_ptr<IQuackBehavior>&& quackBehavior,
		unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		SetFlyBehavior(move(flyBehavior));
		SetQuackBehavior(move(quackBehavior));
		SetDanceBehavior(move(danceBehavior));
	}//добавить смену повидения кряканья
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim() const
	{
		cout << "I'm swimming" << endl;
	}
	void Fly() const
	{
		m_flyBehavior->Fly();
	}
	virtual void Dance() const
	{
		m_danceBehavior->Dance();
	}
	virtual void SetQuackBehavior(unique_ptr<IQuackBehavior>&& quackBehavior)
	{
		assert(quackBehavior);
		m_quackBehavior = move(quackBehavior);
	}
	virtual void SetDanceBehavior(unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = move(danceBehavior);
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceWaltz>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DanceMinuet>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(make_unique<FlyNoWay>());
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetDanceBehavior(make_unique<DanceWaltz>());
	PlayWithDuck(modelDuck);
}