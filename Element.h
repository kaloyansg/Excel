#pragma once
#include <iostream>
#include "my_string.h"
#pragma warning(disable:4996)

class Element
{
public:
	virtual double getNum() const = 0;
	virtual my_string getValueAsStr() const = 0;
	virtual Element* clone() const = 0;

	friend std::ostream& operator<<(std::ostream&, const Element&);
	virtual ~Element() = default;

protected:
	virtual void print(std::ostream&) const;/////////////////////////////////////////////////////////////
};

my_string doubleToStr(double num);

class ElementCreator
{
public:
	ElementCreator();
	virtual ~ElementCreator() = default;
	virtual bool checkType(const my_string&) const = 0;
	virtual Element* createElement(const my_string&, const void*) const = 0;
};