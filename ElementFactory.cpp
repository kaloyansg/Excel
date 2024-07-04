#include "ElementFactory.h"

ElementFactory& ElementFactory::getFactory()
{
    static ElementFactory theFactory;
    return theFactory;
}

void ElementFactory::registerElement(const ElementCreator* creator)
{
    //assert(cnt < MaxNumShapeCreators);
    if (count < MaxNumElCreators)
    {
        creators[count++] = creator;
    }
}

Element* ElementFactory::createElement(const my_string& item, const void* ptr) const
{
    for (size_t i = 0; i < count; ++i)
    {
        if (creators[i])///////////////////////////////////////////////////////////////////
        if (creators[i]->checkType(item))
        {
            return creators[i]->createElement(item, ptr);
        }
    }
    throw std::invalid_argument("Invalid element type");////////////////////////////////////////////////////////
}
