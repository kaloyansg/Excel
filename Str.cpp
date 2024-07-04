#include "Str.h"
#include "Num.h"

Str::Str(const my_string& str) : str(nullptr)
{
    if (!checkStr(str))
        throw std::invalid_argument("Invalid string");

	this->str = str;
    if (!this->str.is_good())
    {
        throw std::bad_alloc();
    }
}

double Str::getNum() const
{
    my_string num;
    size_t size = str.size()-1;
    for (size_t i = 1; i < size; ++i)
    {
        num += str[i];
    }

    if (NumCreator::isInt(num))
    {
        return NumCreator::getIntValue(num);
    }
    else if (NumCreator::isDouble(num))
    {
        return NumCreator::getDoubleValue(num);
    }

	return 0.0;
}

my_string Str::getValueAsStr() const
{
    my_string result;
    size_t size = str.size();
    for (size_t i = 1; i+1 < size; ++i)
    {
        if (str[i] == '\\')
        {
            ++i;
        }
        if (i + 1 < size)
        {
            result += str[i];
        }
    }
	return result;
}

Element* Str::clone() const
{
    return new Str(*this);
}

void Str::print(std::ostream& os) const
{
	os << str;
}

bool Str::checkStr(const my_string& str)
{
    if (str.size() < 3)
    {
        return false;
    }
    //if (str[0] != '\\' || str[1] != '"' || str[str.size() - 2] !='\\' || str[str.size() - 1] != '"')
    if (str[0] != '"' || str[str.size() - 1] != '"')
    {
        return false;
    }

    bool closed = false;
    for (size_t i = 1; i < str.size(); ++i)
    {
        if (str[i] == '\\')
        {
            ++i;
        }
        else if (str[i] == '"')
        {
            closed = true;
        }
        else if (closed)
        {
            return false;
        }
    }

    return closed;
}

bool StrCreator::checkType(const my_string& str) const
{
    if (str.size() < 3)
    {
        return false;
    }
    if (str[0] != '"' || str[str.size() - 1] != '"')
    {
        return false;
    }
    return true;
}

Element* StrCreator::createElement(const my_string& str, const void*) const
{
    return new Str(str);
}

static StrCreator __;