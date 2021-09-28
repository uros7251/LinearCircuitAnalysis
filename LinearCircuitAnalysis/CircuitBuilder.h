#pragma once
#include "InParallel.h"
#include "InSeries.h"
#include "IdealVoltageSource.h"
#include "IdealCurrentSource.h"
#include "Resistor.h"
class CircuitBuilder
{
public:
	CompositeElement* getRealVoltageSource(double emf, double r);
	CompositeElement* getRealCurrentSource(double j, double r);
	static CircuitBuilder* getInstance();
protected:
	CircuitBuilder() {}
private:
	static CircuitBuilder* _instance;
};

