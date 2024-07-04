#include "Formula.h"

Formula::Formula(const my_string& item, Table* matrix)
{
    if (!isFormula(item))
        throw std::invalid_argument("Invalid formula");

    /*this->lhs = getLHS(item);
    this->symbol = getSymbol(item);
    this->rhs = getRHS(item);*/
    getFormula(item, this->lhs, this->symbol, this->rhs);
    this->met = false;
    this->matrix = matrix;
}

double Formula::getNum() const
{
    if (this->met)
    {
        throw std::invalid_argument("Invalid sequence of formulas");
    }

    this->met = true;

    double lLiteral = 0, rLiteral = 0;

    if (isAdress(lhs))
    {
        int row = getRow(lhs);
        int column = getColumn(lhs);
        if (row > matrix->getRows() || column > matrix->getColumns())
        {
            lLiteral = 0;
        }
        else try
        {
            if (matrix->getElements()[row - 1][column - 1] != nullptr)
            {
                lLiteral = matrix->getElements()[row - 1][column - 1]->getNum(); //index-1, cause the users count stranting from 1
            }
            else
            {
                lLiteral = 0;
            }
        }
        catch (...)
        {
            this->met = false;
            throw;
        }
    }
    else
    {
        lLiteral = getDoubleValue(lhs);
    }

    if (symbol.str() == nullptr || symbol.size() == 0)
    {
        this->met = false;
        return lLiteral;
    }

    if (isAdress(rhs))
    {
        int row = getRow(rhs);
        int column = getColumn(rhs);
        if (row > matrix->getRows() || column > matrix->getColumns())
        {
            rLiteral = 0;
        }
        else try
        {
            if (matrix->getElements()[row - 1][column - 1] != nullptr)
            {
                rLiteral = matrix->getElements()[row - 1][column - 1]->getNum();
            }
            else
            {
                rLiteral = 0;
            }
        }
        catch (...)
        {
            this->met = false;
            throw;
        }
    }
    else
    {
        rLiteral = getDoubleValue(rhs);
    }

    if (strcmp(symbol.str(), "+") == 0) 
    {
        this->met = false; 
        return (double)lLiteral + (double)rLiteral;
    }

    if (strcmp(symbol.str(), "-") == 0) 
    {
        this->met = false; 
        return (double)lLiteral - (double)rLiteral;
    }

    if (strcmp(symbol.str(), "*") == 0) 
    {
        this->met = false; 
        return (double)lLiteral * (double)rLiteral;
    }

    if (strcmp(symbol.str(), "/") == 0) 
    {
        this->met = false;
        if (rLiteral != 0)
        {
            return (double)lLiteral / (double)rLiteral;
        }
        else
        {
            throw std::invalid_argument("Division by zero");
        }
    }

    if (strcmp(symbol.str(), "==") == 0) 
    {
        this->met = false; 
        return lLiteral == rLiteral;
    }

    if (strcmp(symbol.str(), "!=") == 0) 
    {
        this->met = false; 
        return lLiteral != rLiteral;
    }

    if (strcmp(symbol.str(), "<") == 0) 
    {
        this->met = false; 
        return lLiteral < rLiteral;
    }

    if (strcmp(symbol.str(), ">") == 0) 
    {
        this->met = false; 
        return lLiteral > rLiteral;
    }

    if (strcmp(symbol.str(), "<=") == 0) 
    {
        this->met = false; 
        return lLiteral <= rLiteral;
    }

    if (strcmp(symbol.str(), ">=") == 0) 
    {
        this->met = false; 
        return lLiteral >= rLiteral;
    }

    this->met = false;
    return 0;
}

my_string Formula::getValueAsStr() const
{
    try
    {
        return doubleToStr(getNum());
    }
    catch (...)
    {
        return "NULL";
        throw;
    }
    
}

Element* Formula::clone() const
{
    return new Formula(*this);
}

void Formula::print(std::ostream& os) const
{
    os << "=" << lhs << symbol << rhs;
}

bool Formula::isAdress(const my_string& hs)
{
    if (hs[0] == 'R')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Formula::getRow(const my_string& hs)
{
    int result = 0;

    for (size_t i = 1; i < hs.size() && hs[i] != 'C'; i++)
    {
        result = result * 10 + hs[i] - '0';
    }

    return result;
}

int Formula::getColumn(const my_string& hs)
{
    int result = 0;
    int index = 1;
    while (hs[index] != 'C')
    {
        index++;
    }
    index++;
    for (index; index < hs.size(); index++)
    {
        result = result * 10 + hs[index] - '0';
    }
    return result;
}

double Formula::getDoubleValue(const my_string& item)
{
    size_t length = item.size();
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

void Formula::getFormula(const my_string& item, my_string& lhs, my_string& symbol, my_string& rhs)
{
    int index = 0;

    while (item[index] != 'R' && item[index] != '+' && item[index] != '-' && !isdigit(item[index]))
    {
        index++;
    }
    lhs += item[index];
    index++;

    while (index < item.size() && (isdigit(item[index]) || item[index] == 'C' || item[index] == '.'))
    {
        lhs += item[index];
        index++;
    }

    ///////////////////////////////////////


    if (index >= item.size())
    {
        return;
    }

    while (index < item.size() &&
        item[index] != '=' && item[index] != '<' && item[index] != '>' && item[index] != '!'
        && item[index] != '+' && item[index] != '-' && item[index] != '*' && item[index] != '/')
    {
        index++;
    }
    if (index >= item.size())
    {
        return;
    }
    symbol += item[index];
    index++;

    if (item[index] == '=')
    {
        symbol += item[index];
    }
    //index++;

    while (item[index] != 'R' && item[index] != '+' && item[index] != '-' && !isdigit(item[index]))
    {
        index++;
    }
    rhs += item[index];
    index++;

    while (index < item.size() && (isdigit(item[index]) || item[index] == 'C' || item[index] == '.'))
    {
        rhs += item[index];
        index++;
    }
}

bool FormulaCreator::checkType(const my_string& item) const
{
    size_t length = item.size();
    size_t index = 0;


    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (item[index] != '=')
    {
        return false;
    }

    return true;
}

Element* FormulaCreator::createElement(const my_string& item, const void* matrixPtr) const
{
    return new Formula(item, (Table*)matrixPtr);
}

//my_string Formula::getLHS(const my_string& item)
//{
//    my_string result;
//    int index = 0;
//
//    while (item[index] != 'R' && item[index] != '+' && item[index] != '-' && !isdigit(item[index]))
//    {
//        index++;
//    }
//    result += item[index];
//    index++;
//
//    while (index < item.size() && (isdigit(item[index]) || item[index] == 'C' || item[index] == '.'))
//    {
//        result += item[index];
//        index++;
//    }
//    return result;
//}
//
//my_string Formula::getSymbol(const my_string& item)
//{
//    int index = 0;
//
//    my_string result;
//
//    while (item[index] != '=')
//    {
//        index++;
//    }
//    index++;
//    
//    while (index < item.size() && 
//        item[index] != '=' && item[index] != '<' && item[index] != '>' && item[index] != '!'
//        && item[index] != '+' && item[index] != '-' && item[index] != '*' && item[index] != '/')
//    {
//        index++;
//    }
//    if (index >= item.size())
//    {
//        return result;
//    }
//    result += item[index];
//    index++;
//
//    if (item[index] == '=')
//    {
//        result += item[index];
//    }
//    return result;
//}
//
//my_string Formula::getRHS(const my_string& item)
//{
//    int index = 0;
//    my_string result;
//
//    while (item[index] != '=')
//    {
//        index++;
//    }
//    index++;
//    while (index < item.size() && 
//        item[index] != '=' && item[index] != '<' && item[index] != '>' && item[index] != '!'
//        && item[index] != '+' && item[index] != '-' && item[index] != '*' && item[index] != '/')
//    {
//        index++;
//    }
//    index++;
//    if (index >= item.size())
//    {
//        return result;
//    }
//    if (item[index] == '=')
//    {
//        index++;
//    }
//
//    while (item[index] != 'R' && item[index] != '+' && item[index] != '-' && !isdigit(item[index]))
//    {
//        index++;
//    }
//    result += item[index];
//    index++;
//
//    while (index < item.size() && (isdigit(item[index]) || item[index] == 'C' || item[index] == '.'))
//    {
//        result += item[index];
//        index++;
//    }
//    return result;
//}

bool Formula::isFormula(const my_string& item)
{
    size_t length = item.size();
    size_t index = 0;

    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (item[index] != '=')
    {
        return false;
    }
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
        while (index < length && (isdigit(item[index]) || item[index] == '.'))
        {
            index++;
            if (item[index] == '.' && !point)
            {
                point = true;
            }
            else if (item[index] == '.' && point)
            {
                return false;
            }
        }
    }
    else
    {
        index++;
        while (index < length && (isdigit(item[index])))
        {
            index++;
        }
        if (item[index] != 'C')
        {
            return false;
        }

        else
        {
            index++;
            if (isdigit(item[index]))
            {
                index++;
            }
            else
            {
                return false;
            }
        }

        while (index < length && isdigit(item[index]))
        {
            index++;
        }
    }

    while (index < length && std::isspace(item[index]))
    {
        index++;
    }

    if (index >= length)
    {
        return true;
    }

    if (item[index] == '+' || item[index] == '-' || item[index] == '*' || item[index] == '/')
    {
        index++;
    }
    else if (item[index] == '=' || item[index] == '!')
    {
        index++;
        if (item[index] != '=')
        {
            return false;
        }
        index++;
    }
    else if (item[index] == '<' || item[index] == '>')
    {
        index++;
        if (item[index] == '=')
        {
            index++;
        }
    }
    else
    {
        return false;
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
        while (index < length && (isdigit(item[index]) || item[index] == '.'))
        {
            index++;
            if (item[index] == '.' && !point)
            {
                point = true;
            }
            else if (item[index] == '.' && point)
            {
                return false;
            }
        }
    }
    else
    {
        index++;
        while (index < length && (isdigit(item[index])))
        {
            index++;
        }
        if (item[index] != 'C')
        {
            return false;
        }

        else
        {
            index++;
            if (isdigit(item[index]))
            {
                index++;
            }
            else
            {
                return false;
            }
        }

        while (index < length)
        {
            if (isdigit(item[index]))
            {
                index++;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

static FormulaCreator __;