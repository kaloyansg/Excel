#pragma once
#include "Element.h"
#include "my_string.h"

class Str : public Element
{
public:
	Str(const my_string&);
	//Str(const Str&) = delete;
	//Str& operator=(const Str&) = delete;
	virtual double getNum() const override;
	virtual my_string getValueAsStr() const override;
	virtual Element* clone() const override;

protected:
	virtual void print(std::ostream&) const override;

private:
	static bool checkStr(const my_string&);

	my_string str;
};

class StrCreator : public ElementCreator
{
public:
	virtual bool checkType(const my_string&) const override;
	virtual Element* createElement(const my_string&, const void*) const override;
};