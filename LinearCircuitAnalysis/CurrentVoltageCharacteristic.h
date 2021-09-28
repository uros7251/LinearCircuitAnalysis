#pragma once
#include <complex>
#include <exception>
#include <iostream>
class CurrentVoltageCharacteristic
{
public:
	CurrentVoltageCharacteristic& operator|=(const CurrentVoltageCharacteristic& other);
	CurrentVoltageCharacteristic& operator&=(const CurrentVoltageCharacteristic& other);
	CurrentVoltageCharacteristic& operator=(const CurrentVoltageCharacteristic& other);
	bool hasFixedVoltage();
	bool hasFixedCurrent();
	std::complex<double> applyVoltage(std::complex<double> voltage);
	std::complex<double> applyCurrent(std::complex<double> current);
	void print();

	static CurrentVoltageCharacteristic* getTypeE(const std::complex<double>& impedance, const std::complex<double>& emf);
	static CurrentVoltageCharacteristic* getTypeJ(const std::complex<double>& currSourceStrength);
	static CurrentVoltageCharacteristic* getParallelNilType();
	static CurrentVoltageCharacteristic* getSeriesNilType();
protected:
	CurrentVoltageCharacteristic(const std::complex<double>& z, const bool v, const std::complex<double>& c);
	std::complex<double> _z, _c;
	bool _v;
};

