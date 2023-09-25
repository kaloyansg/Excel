#include "Formula.h"

bool Formula::isAdress(const Str& hs) const
{
    if (hs[0] == 'R')
        return true;
    else return false;
}

int Formula::getRow(const Str& hs) const
{
    int result = 0;

    for (size_t i = 1; i < hs.GetLenght() && hs[i] != 'C'; i++)
    {
        result = result * 10 + hs[i] - '0';
    }

    return result;
}

int Formula::getColumn(const Str& hs) const
{
    int result = 0;
    int index = 1;
    while (hs[index] != 'C')
    {
        index++;
    }
    index++;
    for (index; index < hs.GetLenght(); index++)
    {
        result = result * 10 + hs[index] - '0';
    }
    return result;
}

double Formula::getDoubleValue(const char* item) const
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

Formula::Formula(const char* lhs, const char* symbol, const char* rhs, Table* matrix)
{
    this->lhs = lhs;
    this->symbol = symbol;
    this->rhs = rhs;
    //this->met = false;
    this->matrix = matrix;
}

double Formula::GetNum() const
{
    if (this->met)
        throw "Invalid sequence of Formulas!";

    this->met = true;

    double lLiteral = 0, rLiteral = 0;

    if (isAdress(lhs))
    {
        if (getRow(lhs) > matrix->getRows() || getColumn(lhs) > matrix->getColumns())
        {
            this->met = false;
            return 0;
        }

        try 
        {
            if (matrix->getElemetns()[getRow(lhs) - 1][getColumn(lhs) - 1] != nullptr)
                lLiteral = matrix->getElemetns()[getRow(lhs) - 1][getColumn(lhs) - 1]->GetNum(); //index-1, cause the users count stranting from 1
            else lLiteral = 0;
        }
        catch (const const char* error)
        {
            this->met = false;
            throw error;
        }
    }
    else
    {
        lLiteral = getDoubleValue(lhs.GetStr());
    }

    if (isAdress(rhs))
    {
        if (getRow(rhs) > matrix->getRows() || getColumn(rhs) > matrix->getColumns())
        {
            this->met = false;
            return 0;
        }
        try
        {
            if (matrix->getElemetns()[getRow(rhs) - 1][getColumn(rhs) - 1] != nullptr)
                rLiteral = matrix->getElemetns()[getRow(rhs) - 1][getColumn(rhs) - 1]->GetNum();
            else rLiteral = 0;
        }
        catch (const const char* error)
        {
            this->met = false;
            throw error;
        }
    }
    else
    {
        rLiteral = getDoubleValue(rhs.GetStr());
    }

    if (strcmp(symbol.GetStr(), "+") == 0) {
        this->met = false; return lLiteral + rLiteral;
    }

    if (strcmp(symbol.GetStr(), "-") == 0) {
        this->met = false; return lLiteral - rLiteral;
    }

    if (strcmp(symbol.GetStr(), "*") == 0) {
        this->met = false; return lLiteral * rLiteral;
    }
    
    if (strcmp(symbol.GetStr(), "/") == 0) {
        this->met = false;
        if (rLiteral != 0)
        {
             return lLiteral / rLiteral;
        }
        else
        {
            throw 0;
        }
    }
    
    if (strcmp(symbol.GetStr(), "==") == 0) {
        this->met = false; return lLiteral == rLiteral;
    }
    
    if (strcmp(symbol.GetStr(), "!=") == 0) {
        this->met = false; return lLiteral != rLiteral;
    }
    
    if (strcmp(symbol.GetStr(), "<") == 0) {
        this->met = false; return lLiteral < rLiteral;
    }
    
    if (strcmp(symbol.GetStr(), ">") == 0) {
        this->met = false; return lLiteral > rLiteral;
    }
    
    if (strcmp(symbol.GetStr(), "<=") == 0) {
        this->met = false; return lLiteral <= rLiteral;
    }
    
    if (strcmp(symbol.GetStr(), ">=") == 0) {
        this->met = false; return lLiteral >= rLiteral;
    }
    
    this->met = false;
    return 0;
}

Str Formula::getValueAsStr() const
{
    try
    {
        return doubleToStr(GetNum());
    }
    catch (const const char* error)
    {
        return "NULL";
    }
    catch (const int& zero)
    {
        return "ERROR";
    }
}

void Formula::Print(std::ostream& os) const
{
    //try
    //{
    //    os << GetNum(); 
    //}
    //catch (const const char* error)
    //{
    //    os << "NULL";
    //}
    //catch (const int& zero)
    //{
    //    os << "ERROR";
    //}

    os << "=" << lhs.GetStr() << symbol.GetStr() << rhs.GetStr();
}
