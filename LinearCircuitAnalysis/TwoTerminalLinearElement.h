#pragma once
#include<complex>
#include<iostream>
#include "CurrentVoltageCharacteristic.h"

const double PI = 3.141592653589793238463;
const double PI_INV = 0.3183098861837907;

enum class ElementType {
	Resistor,
	Capacitor,
	Inductor,
	Switch,
	IdealVoltageSource,
	IdealCurrentSource,
	InParallel,
	InSeries
};

class TwoTerminalLinearElement
{
public:
	TwoTerminalLinearElement();
	/*virtual std::complex<double> getEmf(double omega = 0) = 0;
	virtual std::complex<double> getImpedance(double omega = 0) = 0;*/
	CurrentVoltageCharacteristic* getCurrentVoltageCharacterstic(double freq = 0);
	virtual ElementType getType() = 0;
	friend std::ostream& operator<<(std::ostream& os, TwoTerminalLinearElement& elem);
	virtual ~TwoTerminalLinearElement();
protected:
	virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq) = 0;
	virtual void printInfo(std::ostream & os) = 0;

	CurrentVoltageCharacteristic* _characteristic;
	double _activeFreq;
};

