#include "CircuitBuilder.h"

CircuitBuilder* CircuitBuilder::_instance = nullptr;

CompositeElement* CircuitBuilder::getRealVoltageSource(double emf, double r)
{
    auto ivs = new IdealVoltageSource(emf);
    auto res = new Resistor(r);

    CompositeElement* circuit = new InSeries();
    circuit->Add(ivs);
    circuit->Add(res);

    return circuit;
}

CompositeElement* CircuitBuilder::getRealCurrentSource(double j, double r)
{
    auto ics = new IdealCurrentSource(j);
    auto res = new Resistor(r);

    CompositeElement* circuit = new InParallel();
    circuit->Add(ics);
    circuit->Add(res);

    return circuit;
}

CircuitBuilder* CircuitBuilder::getInstance()
{
    if (_instance == nullptr)
        _instance = new CircuitBuilder();
    return _instance;
}
