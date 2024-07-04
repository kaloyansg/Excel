#include "Num.h"

bool NumCreator::checkType(const my_string& item) const
{
    size_t lenth = item.size();
    size_t beg = 0;

    while (beg < lenth && std::isspace(item[beg]))
    {
        beg++;
    }
    return item[beg] == '+' || item[beg] == '-' || isdigit(item[beg]);
}

Element* NumCreator::createElement(const my_string& item, const void*) const
{
    if (isInt(item))
    {
        return new Num<int>(getIntValue(item));
    }
    if (isDouble(item))
    {
        return new Num<double>(getDoubleValue(item));
    }
    throw std::invalid_argument("Invalid number");
}

bool NumCreator::isInt(const my_string& item)
{
    size_t lenth = item.size();
    size_t beg = 0;

    while (beg < lenth && std::isspace(item[beg]))
    {
        beg++;
    }

    if (beg < lenth && (item[beg] == '+' || item[beg] == '-'))
    {
        beg++;
    }

    for (size_t i = beg; i < lenth; i++)/////////////////int
    {
        if (!std::isdigit(item[i]))
        {
            return false;
        }
    }

    return true;
}

bool NumCreator::isDouble(const my_string& item)
{
    size_t lenth = item.size();
    size_t beg = 0;

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

    for (size_t i = beg + 1; i < lenth; i++)//////////////////////////int
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

int NumCreator::getIntValue(const my_string& item)
{
    size_t length = item.size();
    size_t beg = 0;

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
    for (size_t i = beg; i < length; i++)///////////////////////////////int
    {
        if (!std::isdigit(item[i]))
        {
            break;
        }

        result = (result * 10) + (item[i] - '0');
    }

    return (negative ? -result : result);
}

double NumCreator::getDoubleValue(const my_string& item)
{
    size_t length = item.size();
    size_t beg = 0;

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

    for (size_t i = beg; i < length; i++)/////////////////////////////////////////////int
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

static NumCreator __;