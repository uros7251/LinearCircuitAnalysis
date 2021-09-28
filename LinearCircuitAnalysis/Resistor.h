#pragma once
#include "SingleElement.h"
class Resistor :
    public SingleElement
{
public:
    Resistor(double resistance, char unit = 'O');
    Resistor(std::string name, double resistance, char unit = 'O');
    // Inherited via SingleElement
    /*std::complex<double> getEmf(double omega = 0) override;
    std::complex<double> getImpedance(double omega = 0) override;*/
    ElementType getType() override { return ElementType::Resistor; }
protected:
    // Inherited via SingleElement
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq) override;
    virtual void printInfo(std::ostream& os) override;
private:
    double _resistance;
    static int idPool;

};
