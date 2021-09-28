#include "IdealCurrentSource.h"

int IdealCurrentSource::idPool = 1;

IdealCurrentSource::IdealCurrentSource(double j)
    :IdealCurrentSource("E", j)
{
}

IdealCurrentSource::IdealCurrentSource(std::string name, std::complex<double> j, char unit)
    :SingleElement(name), _j(j)
{
    switch (unit)
    {
    case 'm':
        _j /= 1e3;
        break;
    case 'u':
        _j /= 1e6;
        break;
    case 'n':
        _j /= 1e9;
    default:
        break;
    }
}

IdealCurrentSource::IdealCurrentSource(std::string name, double j, char unit)
    : IdealCurrentSource(name, {j, 0}, unit)
{
}

ElementType IdealCurrentSource::getType()
{
    return ElementType::IdealCurrentSource;
}

CurrentVoltageCharacteristic* IdealCurrentSource::calcCurrentVoltageCharacteristic(double freq)
{
    return CurrentVoltageCharacteristic::getTypeJ(_j);
}

void IdealCurrentSource::printInfo(std::ostream & os)
{
    os << "\"" + _name + "\"=" << _j;
}
