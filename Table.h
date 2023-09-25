#ifndef Table_H
#define Table_H
#pragma once
#include "Element.h"
#include "Str.h"
#include "MyNumber.h"
#include "MyString.h"

class Formula;
#include "Formula.h"

class Table
{
private:
    Element*** elements = nullptr;
    unsigned rows = 0;
    unsigned columns = 0;

    bool isInt(const char* item) const;
    bool isDouble(const char* item) const;
    bool isFormula(const char* item) const;
    int getIntValue(const char* item) const;
    double getDoubleValue(const char* item) const;
    void addRow(unsigned newRows);
    void addColumn(unsigned newColumns);
    const char* getLHS(const  char* item, char*& result) const;
    const char* getSymbol(const  char* item, char*& result) const;
    const char* getRHS(const  char* item, char*& result) const;


public:
    Table();
    Table(const Table& other) = delete;
    Table& operator=(const Table& other) = delete;
    ~Table();

    void addElemets(const char* item, unsigned row, unsigned index);
    void edit(unsigned row, unsigned column, const char* value);
    void print() const;

    Element*** getElemetns() const;
    unsigned getRows() const;
    unsigned getColumns() const;


    void printtt() const; //FOR TESTS
};

#endif /*Table_H*/