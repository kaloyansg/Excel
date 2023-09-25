#pragma once
#include <iostream>
#include "Str.h"
#include <string>
#pragma warning(disable:4996)

class Element
{
public:
	virtual double GetNum() const = 0;
	virtual Str getValueAsStr() const = 0;
	virtual void Print(std::ostream& os) const;
	
	friend std::ostream& operator<<(std::ostream& os, const Element& elem);

	virtual ~Element() = default;
};

Str doubleToStr(double num);