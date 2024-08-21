#ifndef _FUEL_H_
#define _FUEL_H_

class Fuel
{
public:
	Fuel()
		: amountFuel(0)
		, consumptionUnit(1)
	{}

	void setAmountFuel(int curValue)
	{
		amountFuel = curValue;
	}

	int getAmountFuel() const
	{
		return amountFuel;
	}

	void setConsumptionUnit(int curValue)
	{
		consumptionUnit = curValue;
	}

	int getConsumptionUnit() const
	{
		return consumptionUnit;
	}

private:
	int							amountFuel;					// кол-во топлива
	int							consumptionUnit;			// сколько сгорает топлива на одну единицу дистанции
};

#endif /* _FUEL_H_ */