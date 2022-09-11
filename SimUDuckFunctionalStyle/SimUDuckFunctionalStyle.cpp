#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

using DanceBehavior = function<void()>;
void DanceValtz()
{
	cout << "I'm dance waltz" << endl;
}
void DanceMinuet()
{
	cout << "I'm dance minuet" << endl;
}
void DanceNoWay() {};

using FlyBehavior = function<void()>;
void FlyWithWings()
{
	int m_departuresNumber = 1;
	cout << "I'm flying with wings!!" << " my flight number is " << m_departuresNumber << endl;
	m_departuresNumber++;
}
void FlyNoWay() {}

using QuackBehavior = function<void()>;
void QuackSimple()
{
	cout << "Quack Quack!!!" << endl;
}
void Squeak() 
{
	cout << "Squeek!!!" << endl;
}
void MuteQuack() {}	

class Duck
{
public:
	Duck(const FlyBehavior& flyBehavior,
		const QuackBehavior& quackBehavior,
		const DanceBehavior& danceBehavior)
		:m_flyBehavior(flyBehavior),
		m_quackBehavior(quackBehavior),
		m_danceBehavior(danceBehavior)
	{}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	virtual void Dance()
	{
		m_danceBehavior();
	}
	void SetFlyBehavior(const FlyBehavior& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetDanceBehavior(const DanceBehavior& danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, QuackSimple, DanceValtz)
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
		: Duck(FlyWithWings, QuackSimple, DanceMinuet)
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
		: Duck(FlyNoWay, MuteQuack, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, Squeak, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackSimple, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
	void Dance() override {}
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
	mallardDuck.SetFlyBehavior(FlyNoWay);
	PlayWithDuck(mallardDuck);
	mallardDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}