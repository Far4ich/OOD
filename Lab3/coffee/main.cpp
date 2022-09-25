#include <iostream>
#include <string>
#include <functional>
#include "IBeverage.h"
#include "CLemon.h"
#include "CCinnamon.h"
#include "CIceCubes.h"
#include "CChocolateCrumbs.h"
#include "CSyrup.h"
#include "CCoconutFlakes.h"
#include "CCappuccino.h"
#include "CCappuccinoDouble.h"
#include "CLatte.h"
#include "CLatteDouble.h"
#include "COolong.h"
#include "CGreenTea.h"
#include "CWhiteTea.h"
#include "CPuer.h"
#include "CCream.h"
#include "CChocolate.h"
#include "CLiquor.h"

using namespace std;

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

int main()
{
	auto cappucino = make_unique<CCappuccino>();
	cout << cappucino->GetDescription() << ", " << cappucino->GetCost() << endl;

	auto cappucinoDouble = make_unique<CCappuccinoDouble>();
	cout << cappucinoDouble->GetDescription() << ", " << cappucinoDouble->GetCost() << endl;

	auto latte = make_unique<CLatte>();
	cout << latte->GetDescription() << ", " << latte->GetCost() << endl;

	auto latteDouble = make_unique<CLatteDouble>();
	cout << latteDouble->GetDescription() << ", " << latteDouble->GetCost() << endl;

	auto oolong = make_unique<COolong>();
	cout << oolong->GetDescription() << ", " << oolong->GetCost() << endl;

	auto greenTea = make_unique<CGreenTea>();
	cout << greenTea->GetDescription() << ", " << greenTea->GetCost() << endl;

	auto whiteTea = make_unique<CWhiteTea>();
	cout << whiteTea->GetDescription() << ", " << whiteTea->GetCost() << endl;

	auto puer = make_unique<СPuer>();
	cout << puer->GetDescription() << ", " << puer->GetCost() << endl;

	auto tea = make_unique<CTea>();
	cout << tea->GetDescription() << ", " << tea->GetCost() << endl;

	auto teaWithCream = make_unique<CTea>()
		<< MakeCondiment<CCream>();
	cout << teaWithCream->GetDescription() << ", " << teaWithCream->GetCost() << endl;

	auto teaWithChocolates = make_unique<CTea>()
		<< MakeCondiment<CChocolate>(3);
	cout << teaWithChocolates->GetDescription() << ", " << teaWithChocolates->GetCost() << endl;

	//auto teaWithChocolatesError = make_unique<CTea>() << MakeCondiment<CChocolate>(10);

	auto teaWithChocolateLiquor = make_unique<CTea>()
		<< MakeCondiment<CLiquor>(LiquorType::Chocolate);
	cout << teaWithChocolateLiquor->GetDescription() << ", " << teaWithChocolateLiquor->GetCost() << endl;

	auto teaWithWalnutLiquor = make_unique<CTea>()
		<< MakeCondiment<CLiquor>(LiquorType::Walnut);
	cout << teaWithWalnutLiquor->GetDescription() << ", " << teaWithWalnutLiquor->GetCost() << endl;
}
