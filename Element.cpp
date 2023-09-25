#include "Element.h"

std::ostream& operator<<(std::ostream& os, const Element& elem)
{
    elem.Print(os);
    return os;
}

Str doubleToStr(double num) //this method is not mine
{
    std::string str = std::to_string(num);
    
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (!str.empty() && str.back() == '.')
        str.pop_back();

    Str result(str.c_str());
    return result;
}

void Element::Print(std::ostream& os) const
{
    os << " ";
}
