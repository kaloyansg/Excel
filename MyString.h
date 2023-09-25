#pragma once
#include "Element.h"
#include "Str.h"

class MyString : public Element
{
private:
	Str string;

public:
	MyString(Str strnig);

	double GetNum() const override;
	Str getValueAsStr() const override;
	void Print(std::ostream& os) const override;
};