#include "IdealVoltageSource.h"
#include <numbers>
#include <cmath>

int IdealVoltageSource::idPool = 1;

IdealVoltageSource::IdealVoltageSource(double emf)
    :SingleElement("E" + std::to_string(IdealVoltageSource::idPool++)), _emf(emf)
{

}

IdealVoltageSource::IdealVoltageSource(std::string& name, double emf, char unit)
    :IdealVoltageSource(name, {emf, 0}, unit)
{
    
}

IdealVoltageSource::IdealVoltageSource(double emf, double phaseShift)
    :SingleElement("E" + std::to_string(IdealVoltageSource::idPool++))
{
    _emf = std::polar(emf, phaseShift * PI);
}

IdealVoltageSource::IdealVoltageSource(std::string& name, std::complex<double> e, char unit)
    :SingleElement(name), _emf(e)
{
    switch (unit)
    {
    case 'k':
        _emf *= 1e3;
        break;
    case 'm':
        _emf /= 1e3;
        break;
    default:
        break;
    }
}

//std::complex<double> IdealVoltageSource::getEmf(double omega)
//{
//    return _emf;
//}
//
//std::complex<double> IdealVoltageSource::getImpedance(double omega)
//{
//    return std::complex<double>(0, 0);
//}

ElementType IdealVoltageSource::getType()
{
    return ElementType::IdealVoltageSource;
}

CurrentVoltageCharacteristic* IdealVoltageSource::calcCurrentVoltageCharacteristic(double freq)
{
    return CurrentVoltageCharacteristic::getTypeE({ 0,0 }, _emf);
}

void IdealVoltageSource::printInfo(std::ostream & os)
{
    os << "\"" + _name + "\"=" << _emf;
}

