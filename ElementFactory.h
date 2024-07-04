#pragma once
#include "Element.h"

class ElementFactory
{
public:
    static ElementFactory& getFactory();
    void registerElement(const ElementCreator*);
    Element* createElement(const my_string&, const void*) const;

private:
    ElementFactory() :count(0)
    {
        for (size_t i = 0; i < MaxNumElCreators; ++i)
            creators[i] = nullptr;
    }
    ~ElementFactory() = default;
    ElementFactory(const ElementFactory&) = delete;
    ElementFactory& operator=(const ElementFactory&) = delete;

private:
    static const int MaxNumElCreators = 4;//////////////////////////////////////////////////////////////////////////////
    const ElementCreator* creators[MaxNumElCreators];
    size_t count;
};