#include "Inductor.h"

const double Inductor::scale = 1e3;
int Inductor::idPool = 1;

Inductor::Inductor(double inductance, const char unit)
    :SingleElement("L" + std::to_string(Inductor::idPool)), _inductance(inductance)
{
    switch (unit)
    {
    case 'H':
        _inductance *= 1e3;
        break;
    case 'u':
        _inductance /= 1e3;
        break;
    case 'p':
        _inductance /= 1e6;
    default:
        break;
    }
}

Inductor::Inductor(std::string& name, double inductance, const char unit)
    :SingleElement(name), _inductance(inductance)
{
    switch (unit)
    {
    case 'H':
        _inductance *= 1e3;
        break;
    case 'u':
        _inductance /= 1e3;
        break;
    case 'p':
        _inductance /= 1e6;
    default:
        break;
    }
}

ElementType Inductor::getType()
{
    return ElementType::Inductor;
}

void Inductor::printInfo(std::ostream& os)
{
    os << "\"" + _name + "\"=" << _inductance;
}

CurrentVoltageCharacteristic* Inductor::calcCurrentVoltageCharacteristic(double freq)
{
    return CurrentVoltageCharacteristic::getTypeE({ 0, (2 * PI * freq * _inductance) / scale }, { 0, 0 });
}
