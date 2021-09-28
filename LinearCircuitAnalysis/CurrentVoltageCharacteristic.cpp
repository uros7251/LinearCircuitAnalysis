#include "CurrentVoltageCharacteristic.h"

CurrentVoltageCharacteristic::CurrentVoltageCharacteristic(const std::complex<double>& z, const bool v, const std::complex<double>& c)
	:_z(z), _c(c), _v(v)
{
}

CurrentVoltageCharacteristic& CurrentVoltageCharacteristic::operator|=(const CurrentVoltageCharacteristic& other)
{
	// both characteristics are of J-type
	if (this->_v == false && other._v == false)
		this->_c += other._c;
	// first J-type, second E-type
	else if (this->_v == false && other._v == true) {
		this->_z = other._z;
		this->_v = true;
		this->_c = this->_c * other._z + other._c;
	}
	// first E-type, second J-type
	else if (this->_v == true && other._v == false)
		this->_c += other._c * this->_z;
	// both E-type
	else {
		if (this->_z == 0.0 && other._z == 0.0)
			throw std::exception("Error! Voltage conflict!\n");
		this->_c = (this->_c * other._z + other._c * this->_z) / (this->_z + other._z);
		this->_z *= other._z / (this->_z + other._z);
	}
	return *this;
}

CurrentVoltageCharacteristic& CurrentVoltageCharacteristic::operator&=(const CurrentVoltageCharacteristic& other)
{
	// both characteristics are of J-type representing two ideal current sources
	if (this->_v == false && other._v == false)
		throw std::exception("Error! Current conflict!\n");
	// first E-type, second J-type
	else if (this->_v == true && other._v == false) {
		this->operator=(other);
	}
	// first J-type, second E-type
	// both E-type
	else if (this->_v == true && other._v == true)  {
		this->_z += other._z;
		this->_c += other._c;
	}
	return *this;
}

CurrentVoltageCharacteristic& CurrentVoltageCharacteristic::operator=(const CurrentVoltageCharacteristic& other)
{
	this->_z = other._z;
	this->_v = other._v;
	this->_c = other._c;
	return *this;
}

bool CurrentVoltageCharacteristic::hasFixedVoltage()
{
	return _v && _z == 0.0;
}

bool CurrentVoltageCharacteristic::hasFixedCurrent()
{
	return !_v && _c == 0.0;
}

std::complex<double> CurrentVoltageCharacteristic::applyVoltage(std::complex<double> voltage)
{
	if (!_v)
		return _c;
	else if (_z == 0.0)
		throw std::exception("Error! Applying voltage to zero-impedance circuit!");
	else
		return (_c - voltage) / _z;
}

std::complex<double> CurrentVoltageCharacteristic::applyCurrent(std::complex<double> current)
{
	if (!_v)
		throw std::exception("Error! Applying current to infinite-impedance circuit!");
	else
		return _c - current * _z;
}

void CurrentVoltageCharacteristic::print()
{
	if (_v == true) {
		std::cout << ">> Equivalent EMF: " << _c << std::endl;
		std::cout << ">> Equivalent impedance: " << _z << std::endl;
	}
	else
		std::cout << ">> Equivalent current source: " << _c << std::endl;
}

CurrentVoltageCharacteristic* CurrentVoltageCharacteristic::getTypeE(const std::complex<double>& impedance, const std::complex<double>& emf)
{
	return new CurrentVoltageCharacteristic(impedance, true, emf);
}

CurrentVoltageCharacteristic* CurrentVoltageCharacteristic::getTypeJ(const std::complex<double>& currSourceStrength)
{
	return new CurrentVoltageCharacteristic(std::complex<double>(1), false, currSourceStrength);
}

CurrentVoltageCharacteristic* CurrentVoltageCharacteristic::getParallelNilType()
{
	return getTypeJ(std::complex<double>(0, 0));
}

CurrentVoltageCharacteristic* CurrentVoltageCharacteristic::getSeriesNilType()
{
	std::complex<double> nil(0, 0);
	return getTypeE(nil, nil);
}
