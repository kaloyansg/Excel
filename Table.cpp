#include "Table.h"
#pragma warning (disable:4996)

Table::Table()
{
	elements = new Element * *[0];
	rows = 0;
	columns = 0;
}

Table::~Table()
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            delete elements[i][j];
        }
        delete[] elements[i];
    }
    delete[] elements;
}

void Table::addElemets(const char* item, unsigned row, unsigned index)
{
    if (row+1 > this->rows) addRow(row+1);
    if (index+1 > this->columns) addColumn(index+1);

    if (strcmp(item, "") == 0)
    {
        elements[row][index] = nullptr;
        return;
    }

    if (isInt(item))
    {
        elements[row][index] = new MyNumber<int>(getIntValue(item));
        return;
    }
    if (isDouble(item))
    {
        elements[row][index] = new MyNumber<double>(getDoubleValue(item));
        return;
    }

    if (isFormula(item))
    {
        char* lhs = nullptr;
        char* symbol = nullptr;
        char* rhs = nullptr;
        elements[row][index] = new Formula(getLHS(item, lhs), getSymbol(item, symbol), getRHS(item, rhs), this);
        delete[] lhs;
        delete[] symbol;
        delete[] rhs;
        return;
    }

    elements[row][index] = new MyString(item);
}

void Table::edit(unsigned row, unsigned column, const char* value)
{
    addElemets(value, row, column);
}

void Table::addRow(unsigned newRows)
{
    Element*** temp = new Element * *[newRows];
        size_t index = 0;
    try
    {
        for (index; index < newRows; index++)
        {
            temp[index] = new Element * [columns];
            for (size_t j = 0; j < columns; j++)
            {
                temp[index][j] = nullptr;
            }
        }
    }
    catch (const std::bad_alloc& error)
    {
        for (size_t i = 0; i < index; i++)
        {
            delete[]  temp[i];
        }
        delete[] temp;

        throw error;
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            temp[i][j] = this->elements[i][j];
        }
    }

    for (size_t i = 0; i < rows; i++)
    {
        if (this->elements[i] != nullptr)
            delete[] this->elements[i];
    }
    delete[] this->elements;

    this->elements = temp;
    this->rows = newRows;
}

void Table::addColumn(unsigned newColumns)
{
    Element*** temp = new Element * *[rows];

    size_t index = 0;
    try
    {
        for (index; index < rows; index++)
        {
            temp[index] = new Element * [newColumns];
            for (size_t j = 0; j < newColumns; j++)
            {
                temp[index][j] = nullptr;
            }
        }
    }
    catch (const std::bad_alloc& error)
    {
        for (size_t i = 0; i < index; i++)
        {
            delete[]  temp[i];
        }
        delete[] temp;

        throw error;
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            temp[i][j] = this->elements[i][j];
        }
    }
    
    for (size_t i = 0; i < rows; i++)
    {
        if (this->elements[i] != nullptr)
            delete[] this->elements[i];
    }
    delete[] this->elements;

    this->elements = temp;
    this->columns = newColumns;
}

bool Table::isInt(const char* item) const
{
    int lenth = strlen(item);
    int beg = 0;

    while (beg < lenth && std::isspace(item[beg]))
    {
        beg++;
    }

    if (beg < lenth && (item[beg] == '+' || item[beg] == '-'))
    {
        beg++;
    }

    for (int i = beg; i < lenth; i++) 
    {
        if (!std::isdigit(item[i]))
        {
            return false;
        }
    }

    return true;
}

bool Table::isDouble(const char* item) const
{
    int lenth = strlen(item);
    int beg = 0;

    while (beg < lenth && std::isspace(item[beg]))
    {
        beg++;
    }

    if (beg < lenth && (item[beg] == '+' || item[beg] == '-'))
    {
        beg++;
    }

    if (beg < lenth && !std::isdigit(item[beg]) && item[beg] != '.')
    {
        return false;
    }

    bool decimalPointSeen = false;

    for (int i = beg + 1; i < lenth; i++) 
    {
        if (item[i] == '.') 
        {
            if (decimalPointSeen)
            {
                return false;
            }
            decimalPointSeen = true;
        }
        else if (!std::isdigit(item[i])) 
        {
            return false;
        }
    }

    return true;
}

bool Table::isFormula(const char* item) const
{
    int length = strlen(item);
    int index = 0;

    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (item[index] != '=') return false;
    index++;

    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (item[index] != 'R')
    {
        if (item[index] == '+' || item[index] == '-') //first symbol has to be + or -
        {
            index++;
        }
        else if (isdigit(item[index])) //or a digit
        {
            index++;
        }
        else
        {
            return false;
        }

        bool point = false;
        while ((isdigit(item[index]) || item[index] == '.') && index < length)
        {
            index++;
            if (item[index] == '.' && !point) point = true;
            else if (item[index] == '.' && point) return false;
        }
    }
    else
    {
        index++;
        while ((isdigit(item[index])) && index < length)
        {
            index++;
        }
        if (item[index] != 'C')
            return false;

        else
        {
            index++;
            if (isdigit(item[index])) index++;
            else return false;
        }

        while (isdigit(item[index]) && index < length)
        {
            index++;
        }
    }

    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (item[index] == '+' || item[index] == '-' || item[index] == '*' || item[index] == '/')
    {
        index++;
    }
    else if (item[index] == '=' || item[index] == '!')
    {
        index++;
        if (item[index] != '=') return false;
        index++;
    }
    else if (item[index] == '<' || item[index] == '>')
    {
        index++;
        if (item[index] == '=')
            index++;
    }

    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (item[index] != 'R')
    {
        if (item[index] == '+' || item[index] == '-') //first symbol has to be + or -
        {
            index++;
        }
        else if (isdigit(item[index])) //or a digit
        {
            index++;
        }
        else
        {
            return false;
        }

        bool point = false;
        while ((isdigit(item[index]) || item[index] == '.') && index < length)
        {
            index++;
            if (item[index] == '.' && !point) point = true;
            else if (item[index] == '.' && point) return false;
        }
    }
    else
    {
        index++;
        while ((isdigit(item[index])) && index < length)
        {
            index++;
        }
        if (item[index] != 'C')
            return false;

        else
        {
            index++;
            if (isdigit(item[index])) index++;
            else return false;
        }

        while (isdigit(item[index]) && index < length)
        {
            index++;
        }
    }

    return true;
}

int Table::getIntValue(const char* item) const
{
    int length = strlen(item);
    int beg = 0;

    while (beg < length && std::isspace(item[beg]))
    {
        beg++;
    }

    bool negative = false;
    if (beg < length && (item[beg] == '+' || item[beg] == '-'))
    {
        negative = (item[beg] == '-');
        beg++;
    }

    int result = 0;
    for (int i = beg; i < length; i++)
    {
        if (!std::isdigit(item[i]))
        {
            break;
        }

        result = (result * 10) + (item[i] - '0');
    }

    return (negative ? -result : result);
}

double Table::getDoubleValue(const char* item) const
{
    int length = strlen(item);
    int beg = 0;

    while (beg < length && std::isspace(item[beg]))
    {
        beg++;
    }

    bool negative = false;
    if (beg < length && (item[beg] == '+' || item[beg] == '-'))
    {
        negative = (item[beg] == '-');
        beg++;
    }

    double result = 0.0;
    bool point = false;
    double decimalPart = 0.1;

    for (int i = beg; i < length; i++)
    {
        if (std::isdigit(item[i]))
        {
            if (point)
            {
                result += (item[i] - '0') * decimalPart;
                decimalPart *= 0.1;
            }
            else
            {
                result = (result * 10.0) + (item[i] - '0');
            }
        }
        else if (item[i] == '.' && !point)
        {
            point = true;
        }
        else
        {
            break;
        }
    }

    return (negative ? -result : result);
}

const char* Table::getLHS(const char* item, char*& result) const
{
    int index = 0;
    result = new char[strlen(item) + 1];
    int resultIndex = 0;

    while (item[index] != 'R' && item[index] != '+' && item[index] != '-' && !isdigit(item[index]))
    {
        index++;
    }
    result[resultIndex] = item[index]; //first char from the HS
    index++;
    resultIndex++;

    while (isdigit(item[index]) || item[index] == 'C' || item[index] == '.')
    {
        result[resultIndex] = item[index];
        index++;
        resultIndex++;
    }

    result[resultIndex] = '\0';

    return result;
}

const char* Table::getSymbol(const char* item, char*& result) const
{
    int index = 0;

    result = new char[strlen(item) + 1];
    int resultIndex = 0;

    while (item[index] != '=') //skip the first '='
    {
        index++;
    }
    index++;

    while (item[index] != '=' && item[index] != '<' && item[index] != '>' && item[index] != '!'
        && item[index] != '+' && item[index] != '-' && item[index] != '*' && item[index] != '/')
    {
        index++;
    }
    result[resultIndex] = item[index];
    resultIndex++;
    index++;

    if (item[index] == '=')
    {
        result[resultIndex] = item[index];
        resultIndex++;
    }

    result[resultIndex] = '\0';

    return result;
}

const char* Table::getRHS(const char* item, char*& result) const
{
    int index = 0;
    result = new char[strlen(item) + 1];
    int resultIndex = 0;

    while (item[index] != '=') //skip the first '='
    {
        index++;
    }
    index++;
    while (item[index] != '=' && item[index] != '<' && item[index] != '>' && item[index] != '!' 
        && item[index] != '+' && item[index] != '-' && item[index] != '*' && item[index] != '/')
    {
        index++;
    }
    index++;
    if (item[index] == '=')
    {
        index++;
    }

    while (item[index] != 'R' && item[index] != '+' && item[index] != '-' && !isdigit(item[index]))
    {
        index++;
    }
    result[resultIndex] = item[index]; //first char from the HS
    index++;
    resultIndex++;

    while (isdigit(item[index]) || item[index] == 'C' || item[index] == '.')
    {
        result[resultIndex] = item[index];
        index++;
        resultIndex++;
    }

    result[resultIndex] = '\0';

    return result;
}

Element*** Table::getElemetns() const
{
    return elements;
}

unsigned Table::getRows() const
{
    return rows;
}

unsigned Table::getColumns() const
{
    return columns;
}

void Table::print() const
{

    unsigned* charsPerColummn = new unsigned[columns];
    for (size_t i = 0; i < columns; i++)
    {
        charsPerColummn[i] = 0;
    }

    for (size_t j = 0; j < columns; j++)
    {
        for (size_t i = 0; i < rows; i++)
        {
            Str string;
            if (elements[i][j] != nullptr)
                string = elements[i][j]->getValueAsStr();
            else string = " ";

            if (string.GetLenght() > charsPerColummn[j])
            {
                charsPerColummn[j] = string.GetLenght();
            }
        }
    }

    Str element;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (elements[i][j] != nullptr)
                element = elements[i][j]->getValueAsStr();
            else element = " ";
            
            for (size_t c = 0; c < charsPerColummn[j] - element.GetLenght(); c++)
            {
                std::cout << " ";
            }

            std::cout << element.GetStr() << " | ";
        }
        std::cout << std::endl;
    }

    delete[] charsPerColummn;
}

void Table::printtt() const //FOR TESTS
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (elements[i][j] != nullptr)
                std::cout << *elements[i][j] << "; ";
            else
                std::cout << " ; ";
        }
        std::cout << std::endl;
    }
}
