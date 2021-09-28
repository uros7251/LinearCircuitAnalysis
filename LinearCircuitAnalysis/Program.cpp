#include "LCParser.h"
#include "CircuitBuilder.h"
#include <iostream>
const double freq = 50;

//int main() {
//	auto builder = CircuitBuilder::getInstance();
//	auto parallel = (new InParallel())
//		->Add(builder->getRealVoltageSource(10, 6))
//		->Add((new InSeries())
//			->Add(new Resistor(1))
//			->Add(new Capacitor(1)))
//		->Add(new IdealCurrentSource(3));
//	parallel->getCurrentVoltageCharacterstic(omega)->print();
//	std::cout << *parallel;
//	delete parallel;
//}

int main() {
	TwoTerminalLinearElement* circuit = nullptr;
	try {
		if ((circuit = LCParser::loadFromFile("TheveninExample.txt")) == nullptr)
			return -1;
		//circuit = LCParser::parseLC(circuitDesc);
		std::cout << *circuit << std::endl;
		std::cout << "Current-Voltage characteristic at frequency of " << freq << "Hz:" << std::endl;
		circuit->getCurrentVoltageCharacterstic(freq)->print();
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
	delete circuit;
}