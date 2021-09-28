#include "TwoTerminalLinearElement.h"

std::ostream& operator<<(std::ostream& os, TwoTerminalLinearElement& elem)
{
	elem.printInfo(os);
	return os;
}

TwoTerminalLinearElement::TwoTerminalLinearElement()
	:_characteristic(nullptr), _activeFreq(0)
{
}

CurrentVoltageCharacteristic* TwoTerminalLinearElement::getCurrentVoltageCharacterstic(double freq)
{
	if (_characteristic == nullptr || _activeFreq != freq) {
		delete _characteristic;
		_characteristic = calcCurrentVoltageCharacteristic(freq);
	}
	return _characteristic;
}

TwoTerminalLinearElement::~TwoTerminalLinearElement()
{
	delete _characteristic;
}
