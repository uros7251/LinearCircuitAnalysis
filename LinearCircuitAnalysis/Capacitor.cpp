#include "Capacitor.h"

int Capacitor::idPool = 1;
const double Capacitor::scale = 1e9;

Capacitor::Capacitor(double capacitance, const char unit)
    :Capacitor("C" + std::to_string(Capacitor::idPool++), capacitance, unit)
{
    
}

Capacitor::Capacitor(std::string name, double capacitance, const char unit)
    :SingleElement(name), _capacitance(capacitance)
{
    switch (unit)
    {
    case 'F':
        _capacitance *= 1e9;
        break;
    case 'm':
        _capacitance *= 1e6;
        break;
    case 'u':
        _capacitance *= 1e3;
        break;
    case 'p':
        _capacitance /= 1e3;
    default:
        break;
    }
}

ElementType Capacitor::getType()
{
    return ElementType::Capacitor;
}

void Capacitor::printInfo(std::ostream& os)
{
    os << "\"" + _name + "\"=" << _capacitance;
}

CurrentVoltageCharacteristic* Capacitor::calcCurrentVoltageCharacteristic(double freq)
{
    return freq == 0 ? CurrentVoltageCharacteristic::getTypeJ({ 0, 0 })
        : CurrentVoltageCharacteristic::getTypeE({ 0, -scale * 0.5 * PI_INV / (freq * _capacitance) }, { 0, 0 });
}
