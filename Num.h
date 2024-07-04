#pragma once
#include "Element.h"

template <typename Type>
class Num : public Element
{
public:
	//Num() : value(0) {};
	Num(Type value) : value(value) {};

	double getNum() const override
	{
		return value;
	}

	my_string getValueAsStr() const override	// const my_string& ???????????????????????????????????
	{
		return doubleToStr(getNum());
	}

	virtual Element* clone() const override
	{
		return new Num(*this);
	}

protected:
	void print(std::ostream& os) const override
	{
		os << value;
	}

private:
	Type value;
};

class NumCreator : public ElementCreator
{
public:
	virtual bool checkType(const my_string&) const override;
	virtual Element* createElement(const my_string&, const void*) const override;

	static bool isInt(const my_string&);	//const
	static bool isDouble(const my_string&);
	static int getIntValue(const my_string&);
	static double getDoubleValue(const my_string&);
};

