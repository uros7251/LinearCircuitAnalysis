#include "Resistor.h"

int Resistor::idPool = 1;

Resistor::Resistor(double resistance, char unit)
	:Resistor("R" + std::to_string(Resistor::idPool++), resistance)
{
	
}

Resistor::Resistor(std::string name, double resistance, char unit)
	:SingleElement(name), _resistance(resistance)
{
	switch (unit)
	{
	case 'm':
		_resistance /= 1e3;
		break;
	case 'k':
		_resistance *= 1e3;
		break;
	case 'M':
		_resistance *= 1e6;
		break;
	default:
		break;
	}
}

//std::complex<double> Resistor::getEmf(double omega)
//{
//	return std::complex<double>(0, 0);
//}
//
//std::complex<double> Resistor::getImpedance(double omega)
//{
//	return std::complex<double>(_resistance, 0);
//}

void Resistor::printInfo(std::ostream & os)
{
	os << "\"" + _name + "\"=" << _resistance;
}

CurrentVoltageCharacteristic* Resistor::calcCurrentVoltageCharacteristic(double freq)
{
	return CurrentVoltageCharacteristic::getTypeE({ _resistance, 0 }, { 0, 0 });
}
