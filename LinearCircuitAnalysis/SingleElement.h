#pragma once
#include "TwoTerminalLinearElement.h"
#include <string>
class SingleElement :
    public TwoTerminalLinearElement
{
public:
    SingleElement(std::string name)
        :TwoTerminalLinearElement(), _name(name)
    {}
    std::string getName() {
        return _name;
    }
protected:
    std::string _name;
};