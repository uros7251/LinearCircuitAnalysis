#include "InParallel.h"

InParallel::InParallel()
	:_ivs(nullptr)
{
	_children = new std::list<TwoTerminalLinearElement*>();
}

InParallel::InParallel(TwoTerminalLinearElement* first, TwoTerminalLinearElement* second)
	:InParallel()
{
	Add(first);
	Add(second);
}

CompositeElement* InParallel::Add(TwoTerminalLinearElement* elem)
{
	// prohibited to add a voltage source when there's already one contained
	if (elem->getCurrentVoltageCharacterstic()->hasFixedVoltage()) {
		if (_ivs == nullptr)
			_ivs = elem;
		else
			throw std::exception("Prohibited to add more than one fixed voltage network in parallel!");
	}
	else
		_children->push_back(elem);
	return this;
}

void InParallel::Remove(TwoTerminalLinearElement* elem)
{
	if (_ivs == elem) {
		delete _ivs;
		_ivs = nullptr;
	}
	else
		_children->remove(elem);
}

//std::complex<double> InParallel::getEmf(double omega)
//{
//	if (_children->empty())
//		return std::complex<double>(0, 0);
//	// if there's ideal voltage source among children, return its emf
//	if (_ivs != nullptr)
//		return _ivs->getEmf(omega);
//
//	std::complex<double> emf(0, 0), inv_imp(0, 0), one(1, 0);
//	for (auto it = _children->begin(); it != _children->end(); it++) {
//		emf += (*it)->getEmf(omega) / (*it)->getImpedance();
//		inv_imp += one / (*it)->getImpedance(omega);
//	}
//	return emf / inv_imp;
//}
//
//std::complex<double> InParallel::getImpedance(double omega)
//{
//	if (_children->empty())
//		return std::complex<double>(0, 0);
//	if (_ivs != nullptr)
//		return std::complex<double>(0, 0);
//	std::complex<double> inv_imp(0, 0), one(1, 0);
//	for (auto it = _children->begin(); it != _children->end(); it++) {
//		inv_imp += one / (*it)->getImpedance();
//	}
//	return one / inv_imp;
//}

void InParallel::printInfo(std::ostream & os)
{
	os << "Parallel[";
	for (auto it = _children->begin(); it != _children->end(); it++) {
		os << **it;
		if (*it != _children->back())
			os << ", ";
	}
	os << "]";
}

CurrentVoltageCharacteristic* InParallel::calcCurrentVoltageCharacteristic(double freq)
{
	if (_ivs != nullptr)
		return _ivs->getCurrentVoltageCharacterstic(freq);
	if (_children == nullptr)
		return nullptr;
	CurrentVoltageCharacteristic& characteristic = *CurrentVoltageCharacteristic::getParallelNilType();
	for (auto it = _children->begin(); it != _children->end(); it++) {
		auto ch = (*it)->getCurrentVoltageCharacterstic(freq);
		if (ch != nullptr)
			characteristic |= *ch;
	}
	return &characteristic;
}

InParallel::~InParallel()
{
	for (auto it = _children->begin(); it != _children->end(); it++) {
		delete (*it);
	}
	delete _children;
	delete _ivs;
}

int InParallel::NoOfConstituents()
{
	return _children->size() + _ivs == nullptr ? 0 : 1;
}
