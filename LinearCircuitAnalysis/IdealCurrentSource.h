#pragma once
#include "SingleElement.h"
class IdealCurrentSource :
    public SingleElement
{
public:
    IdealCurrentSource(double j);
    IdealCurrentSource(std::string name, std::complex<double> j, char unit = 'A');
    IdealCurrentSource(std::string name, double j, char unit = 'A');
    // Inherited via SingleElement
    virtual ElementType getType() override;
protected:
    // Inherited via SingleElement
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq = 0) override;
    virtual void printInfo(std::ostream& os) override;
private:
    std::complex<double> _j;
    static int idPool;
    
};

