#include "Element.h"
#include "ElementFactory.h"
#include <string>

std::ostream& operator<<(std::ostream& os, const Element& elem)
{
    elem.print(os);
    return os;
}

my_string doubleToStr(double num) //this method is not mine
{
    std::string str = std::to_string(num);

    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (!str.empty() && str.back() == '.')
    {
        str.pop_back();
    }

    my_string result(str.c_str());
    return result;
}

void Element::print(std::ostream& os) const
{
    os << " ";
}

ElementCreator::ElementCreator()
{
    ElementFactory::getFactory().registerElement(this);
}
