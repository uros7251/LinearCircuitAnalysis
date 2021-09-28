#pragma once
#include "CompositeElement.h"
#include <list>
class InSeries :
    public CompositeElement
{
public:
    InSeries();
    InSeries(TwoTerminalLinearElement* first, TwoTerminalLinearElement* second);

    // Inherited via CompositeElement
    int NoOfConstituents() override;
    CompositeElement* Add(TwoTerminalLinearElement* elem) override;
    void Remove(TwoTerminalLinearElement* elem) override;
    ElementType getType() override { return ElementType::InSeries; }

    ~InSeries();

    /*std::complex<double> getEmf(double omega = 0) override;
    std::complex<double> getImpedance(double omega = 0) override;*/
protected:
    // Inherited via CompositeElement
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq) override;
    virtual void printInfo(std::ostream& os) override;
private:
    std::list<TwoTerminalLinearElement*>* _children;
    TwoTerminalLinearElement* _ics;
};

