#pragma once
#include "CompositeElement.h"
#include <list>
class InParallel :
    public CompositeElement
{
public:
    InParallel();
    InParallel(TwoTerminalLinearElement* first, TwoTerminalLinearElement* second);

    // Inherited via CompositeElement
    int NoOfConstituents() override;
    CompositeElement* Add(TwoTerminalLinearElement* elem) override;
    void Remove(TwoTerminalLinearElement* elem) override;
    ElementType getType() override { return ElementType::InParallel; }

    ~InParallel();
    
    /*std::complex<double> getEmf(double omega = 0) override;
    std::complex<double> getImpedance(double omega = 0) override;*/
protected:
    // Inherited via CompositeElement
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq) override;
    virtual void printInfo(std::ostream& os);
private:
    std::list<TwoTerminalLinearElement*>* _children;
    TwoTerminalLinearElement* _ivs;
};

