#pragma once
#include "SingleElement.h"
class Inductor :
    public SingleElement
{
public:
    Inductor(double inductance, const char unit = 'm');
    Inductor(std::string& name, double inductance, const char unit = 'm');
    // Inherited via SingleElement
    virtual ElementType getType() override;
protected:
    virtual void printInfo(std::ostream& os) override;
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq = 0) override;
private:
    double _inductance;
    static const double scale; // unit is mH
    static int idPool;
};