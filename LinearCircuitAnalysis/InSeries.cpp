#include "InSeries.h"

InSeries::InSeries()
	:_ics(nullptr)
{
	_children = new std::list<TwoTerminalLinearElement*>();
}

InSeries::InSeries(TwoTerminalLinearElement* first, TwoTerminalLinearElement* second)
	:InSeries()
{
	Add(first);
	Add(second);
}

CompositeElement* InSeries::Add(TwoTerminalLinearElement* elem)
{	// prohibited to add a current source when there's already one contained
	if (elem->getCurrentVoltageCharacterstic()->hasFixedCurrent()) {
		if (_ics == nullptr)
			_ics = elem;
		else
			throw std::exception("Prohibited to add more than one fixed current network in parallel!");
	}
	else
		_children->push_back(elem);
	return this;
}

void InSeries::Remove(TwoTerminalLinearElement* elem)
{
	if (_ics == elem) {
		delete _ics;
		_ics = nullptr;
	}
	else
		_children->remove(elem);
}

//std::complex<double> InSeries::getEmf(double omega)
//{
//	std::complex<double> emf(0, 0);
//	for (auto it = _children->begin(); it != _children->end(); it++)
//		emf += (*it)->getEmf(omega);
//	return emf;
//}
//
//std::complex<double> InSeries::getImpedance(double omega)
//{
//	std::complex<double> imp(0, 0);
//	for (auto it = _children->begin(); it != _children->end(); it++)
//		imp += (*it)->getImpedance(omega);
//	return imp;
//}

InSeries::~InSeries()
{
	for (auto it = _children->begin(); it != _children->end(); it++) {
		delete (*it);
	}
	delete _children;
	delete _ics;
}

void InSeries::printInfo(std::ostream & os)
{
	os << "Series[";
	for (auto it = _children->begin(); it != _children->end(); it++) {
		os << **it;
		if (*it != _children->back())
			os << ", ";
	}
	os << "]";
}

CurrentVoltageCharacteristic* InSeries::calcCurrentVoltageCharacteristic(double freq)
{
	if (_ics != nullptr)
		return _ics->getCurrentVoltageCharacterstic(freq);
	if (_children == nullptr)
		return nullptr;
	CurrentVoltageCharacteristic& characteristic = *CurrentVoltageCharacteristic::getSeriesNilType();
	for (auto it = _children->begin(); it != _children->end(); it++) {
		auto ch = (*it)->getCurrentVoltageCharacterstic(freq);
		if (ch != nullptr)
			characteristic &= *ch;
	}
	return &characteristic;
}

int InSeries::NoOfConstituents()
{
	return _children->size() + _ics == nullptr ? 0 : 1;
}