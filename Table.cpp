#include "Table.h"
#include <fstream>

Table::Table() : elements(nullptr), rows(0), columns(0)
{}

Table::~Table()
{
    if (elements)
    for (size_t i = 0; i < rows; i++)
    {
        if (elements[i])
        for (size_t j = 0; j < columns; ++j)
        {
            delete elements[i][j];
        }
        delete[] elements[i];
    }
    delete[] elements;
    elements = nullptr;
}

void Table::addElements(const my_string& item, size_t row, size_t index)
{
    try
    {
        if (row + 1 > this->rows || index + 1 > this->columns)
        {
            expandTable(row + 1, index + 1);
        }
        /*if (row + 1 > this->rows) 
            addRow(row + 1);
        if (index + 1 > this->columns) 
            addColumn(index + 1);*/
    }
    catch (...)
    {
        throw std::bad_alloc();
    }

    if (item.str() == nullptr || item.size() == 0)
    {
        return;
    }

    try
    {
        Element* newEl = ElementFactory::getFactory().createElement(item, this);
        delete elements[row][index];
        elements[row][index] = newEl;
    }
    catch (...)
    {
        throw;
    }
}

void Table::edit(size_t row, size_t index, const my_string& newVal)
{
    if (row > this->rows || index > this->columns)
    {
        throw std::invalid_argument("Invalid adress, there is not a cell with such an adress in the table!");
    }
    addElements(newVal, row, index);
}

void Table::print(std::ostream& os) const
{
    size_t* charsPerColummn = new size_t[columns] {0};

    for (size_t j = 0; j < columns; j++)
    {
        for (size_t i = 0; i < rows; i++)
        {
            my_string string;
            if (elements[i][j] != nullptr)
            {
                string = elements[i][j]->getValueAsStr();
            }
            else 
            {
                string = " ";
            }

            if (string.size() > charsPerColummn[j])
            {
                charsPerColummn[j] = string.size();
            }
        }
    }

    my_string element;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (elements[i][j] != nullptr)
            {
                element = elements[i][j]->getValueAsStr();
            }
            else
            {
                element = " ";
            }

            for (size_t c = 0; c < charsPerColummn[j] - element.size(); c++)
            {
                os << " ";
            }

            os << element.str() << " | ";
        }
        os << std::endl;
    }

    delete[] charsPerColummn;
}

Element*** Table::getElements() const
{
    return elements;
}

size_t Table::getRows() const
{
    return rows;
}

size_t Table::getColumns() const
{
    return columns;
}

void Table::open(Table*& table, const my_string& fileName, std::ostream& out)
{
    std::ifstream file(fileName.str());
    if (!file)
    {
        file.close();
        throw std::invalid_argument("File not found!");
    }

    char a;
    file >> a;
    if (file.eof())
    {
        file.close();
        throw std::invalid_argument("Empty file!");
    }

    file.seekg(0, std::ios::beg);

    table = new Table(); ///////////////////////////////////////////////////////////////////////////////
    my_string item;
    size_t currC = 0;
    size_t currR = 0;

    file.get(a);
    while (!file.eof())
    {
        if (!file)
        {
            file.close();
            throw std::invalid_argument("File corruption!");
        }
        /*if (a < 0 || a>127)
        {
            file.close();
            throw std::invalid_argument("Invalid file - Invalid symbol!");
        }*/
        if (a == ',')
        {
            try
            {
                table->addElements(item, currR, currC);
            }
            catch (const std::invalid_argument& err)
            {
                out << "*" << err.what() << " at(" << currR + 1 << "," << currC + 1 << ")" << '\n';
            }
            currC++;
            item = "";
        }
        else if (a == '\n')
        {
            try
            {
                table->addElements(item, currR, currC);
            }
            catch (const std::invalid_argument& err)
            {
                out << "*" << err.what() << '\n';
            }
            currR++;
            currC = 0;
            item = "";
        }
        else if (a != '\0')
        {
            item += a;
        }
        file.get(a);
    }
    table->addElements(item, currR, currC);

    file.close();
    //return table;/////////////////////////////////////////////////////////////////////////////
}

void Table::save(const my_string& fileName) const
{
    std::ofstream file(fileName.str());
    if (!file)
    {
        file.close();
        throw std::invalid_argument("File not loaded!");
    }

    size_t rows = getRows();
    size_t columns = getColumns();
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (getElements()[i][j])
            {
                file << *getElements()[i][j];
            }

            if (j + 1 < columns)
            {
                file << ",";
            }
        }
        if (i + 1 < rows)
        {
            file << "\n";
        }
    }
    file.close();
}

void Table::testPrint() const
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (elements[i][j] != nullptr)
            {
                std::cout << *elements[i][j] << "; ";
            }
            else
            {
                std::cout << " ; ";
            }
        }
        std::cout << std::endl;
    }
}

void Table::expandTable(size_t newRows, size_t newColumns)
{
    newRows = std::max(rows, newRows);
    newColumns = std::max(columns, newColumns);

    Element*** temp = new Element * *[newRows] {nullptr};
    try
    {
        for (size_t i = 0; i < newRows; i++)
        {
            temp[i] = new Element * [newColumns] {nullptr};
        }
    }
    catch (const std::bad_alloc&)
    {
        for (size_t i = 0; i < newRows; i++)
        {
            delete[] temp[i];
        }
        delete[] temp;
        throw;
    }

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            temp[i][j] = elements[i][j]; //shallow copy
        }
    }
    
    for (size_t i = 0; i < rows; i++)
    {
        delete[] elements[i];
    }
    delete[] elements;
    elements = temp;

    this->rows = newRows;
    this->columns = newColumns;
}
