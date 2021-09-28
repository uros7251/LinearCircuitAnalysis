#pragma once
#include "SingleElement.h"
class Capacitor :
    public SingleElement
{
public:
    Capacitor(std::string name, double capacitance, const char unit = 'n');
    Capacitor(double capacitance, const char unit = 'n');
    // Inherited via SingleElement
    virtual ElementType getType() override;
protected:
    virtual void printInfo(std::ostream& os) override;
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq = 0) override;
private:
    double _capacitance;
    static int idPool;
    static const double scale; // unit is nF
};