#pragma once
#include "TwoTerminalLinearElement.h"
#include <exception>
class CompositeElement :
    public TwoTerminalLinearElement
{
public:
    CompositeElement() :TwoTerminalLinearElement() {}
    virtual CompositeElement* Add(TwoTerminalLinearElement* elem) = 0;
    virtual void Remove(TwoTerminalLinearElement* elem) = 0;
    virtual int NoOfConstituents() = 0;
};

