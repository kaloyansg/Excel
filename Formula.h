#pragma once
#include "Element.h"
#include "Table.h"////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <cmath>

class Formula : public Element
{
public:
	Formula(const my_string& str, Table* matrix);
	//Formula(const Formula&) = delete;
	//Formula& operator=(const Formula&) = delete;

	virtual double getNum() const override;
	virtual my_string getValueAsStr() const override;
	virtual Element* clone() const override;

protected:
	virtual void print(std::ostream& os) const override;

private:
	static bool isAdress(const my_string&);
	static int getRow(const my_string&);
	static int getColumn(const my_string&);
	static double getDoubleValue(const my_string&);
	static void getFormula(const my_string&, my_string&, my_string&, my_string&);
	/*static my_string getLHS(const my_string&);
	static my_string getSymbol(const my_string&);
	static my_string getRHS(const my_string&);*/
	static bool isFormula(const my_string&);

private:
	my_string lhs;
	my_string symbol;
	my_string rhs;
	Table* matrix = nullptr; //keeps the adress of the table that the cell is located, in order to have access to the other cells
	mutable bool met; //for avoiding infinite looping in the recurtion in getNum()
};

class FormulaCreator : public ElementCreator
{
public:
	virtual bool checkType(const my_string&) const override;
	virtual Element* createElement(const my_string&, const void*) const override;
};