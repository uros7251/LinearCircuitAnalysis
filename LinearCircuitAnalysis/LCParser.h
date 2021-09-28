#pragma once
#include "LCLexer.h"
#include "InParallel.h"
#include "InSeries.h"
#include "IdealCurrentSource.h"
#include "IdealVoltageSource.h"
#include "Resistor.h"
#include "Inductor.h"
#include "Capacitor.h"
#include "Switch.h"
#include <queue>
#include <fstream>

class LCParser
{
public:
	static TwoTerminalLinearElement* loadFromFile(std::string path);
	static TwoTerminalLinearElement* parseLC(char* buff);
private:
	static SingleElement* parseSingleElement(std::queue<std::string*>* tokens);
	static CompositeElement* parseCompositeElement(std::queue<std::string*>* tokens);
};

