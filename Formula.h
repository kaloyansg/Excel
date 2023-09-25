#ifndef Formula_H
#define Formula_H
#pragma once
#pragma warning (disable:4996)
#include "Element.h"
#include "Str.h"
#include <cmath>

class Table;
#include "Table.h"

class Formula : public Element
{
private:
	Str lhs;
	Str symbol;
	Str rhs;

	Table* matrix = nullptr; //keeps the adress of the table that the cell is located, in order to have access to the other cells

	mutable bool met = false; //for avoiding infinite looping in the recurtion in GetNum()

	bool isAdress(const Str& hs) const;
	int getRow(const Str& hs) const;
	int getColumn(const Str& hs) const;

	double getDoubleValue(const char* item) const;

public:
	Formula(const char* lhs, const char* symbol, const char* rhs, Table* matrix);
	Formula(const Formula&) = delete;
	Formula& operator=(const Formula&) = delete;

	double GetNum() const override;
	Str getValueAsStr() const override;
	void Print(std::ostream& os) const override;
};

#endif /*Formula_H*/