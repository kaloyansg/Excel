#pragma once
#include "Element.h"
#include "ElementFactory.h"
class Table
{
public:
    Table();
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;
    ~Table();

    void addElements(const my_string&, size_t, size_t);
    void edit(size_t, size_t, const my_string&);
    void print(std::ostream&) const;
    void testPrint() const; //FOR TESTS

    Element*** getElements() const;
    size_t getRows() const;
    size_t getColumns() const;

    static void open(Table*&, const my_string&, std::ostream&);
    void save(const my_string&) const;

private:
    void expandTable(size_t, size_t);

private:
	Element*** elements;
	size_t rows;
	size_t columns;
};