#include "Switch.h"
int Switch::idPool = 1;

Switch::Switch(bool closed)
    :SingleElement("S" + std::to_string(Switch::idPool)), _closed(closed)
{
}

ElementType Switch::getType()
{
    return ElementType::Switch;
}

void Switch::printInfo(std::ostream& os)
{
    os << "\"" + _name + "\"=" << _closed ? "1" : "0";
}

CurrentVoltageCharacteristic* Switch::calcCurrentVoltageCharacteristic(double freq)
{
    return _closed ? CurrentVoltageCharacteristic::getTypeE({ 0,0 }, { 0,0 })
        : CurrentVoltageCharacteristic::getTypeJ({ 0,0 });
}
