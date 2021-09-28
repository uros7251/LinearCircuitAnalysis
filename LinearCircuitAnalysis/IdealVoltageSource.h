#pragma once
#include "SingleElement.h"
class IdealVoltageSource :
    public SingleElement
{
public:
    IdealVoltageSource(double emf);
    IdealVoltageSource(std::string& name, double emf, char unit = 'V');
    IdealVoltageSource(double emf, double phaseShift);
    IdealVoltageSource(std::string& name, std::complex<double> e, char unit = 'V');
    // Inherited via SingleElement
    virtual ElementType getType() override;
    /*virtual std::complex<double> getEmf(double omega = 0) override;
    virtual std::complex<double> getImpedance(double omega = 0) override;*/
protected:
    CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq) override;
    virtual void printInfo(std::ostream& os) override;
private:
    std::complex<double> _emf;
    static int idPool;
};
