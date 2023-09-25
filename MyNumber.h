#pragma once
#include "Element.h"

template <typename Type>
class MyNumber : public Element
{
	Type value;

public:
	MyNumber() : value(0) {};
	MyNumber(Type value) : value(value) {};

	double GetNum() const override
	{
		return value;
	}

	Str getValueAsStr() const override
	{
		return doubleToStr(GetNum());
	}

	void Print(std::ostream& os) const override
	{
		os << value;
	}
};