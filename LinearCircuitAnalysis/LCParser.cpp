#include "LCParser.h"
#include<sstream>
const char* BRACE_OPEN_EXCEPTION = "Error! Circuit description ought to start with brace!";
const char* BRACE_CLOSE_EXCEPTION = "Error! Circuit description ought to end with brace!";
const char* INVALID_IDENTIFIER_EXCEPTION = "Error!Invalid identifier!";
const char* COLON_EXCEPTION = "Error! Identifier not followed by a colon!";
const char* BRACKET_OPEN_EXCEPTION = "Error! Token '[' expected after a colon!";
const char* INVALID_COMPOSITE_EXCEPTION = "Invalid composite type!";
const char* COMMA_EXCEPTION = "Error! Comma or closed bracket expected after element definition!";

TwoTerminalLinearElement* LCParser::loadFromFile(std::string path)
{
    char* buff;
    std::ifstream ifs;
    try {
        ifs.open(path);
        // calc length
        ifs.seekg(0, ifs.end);
        int length = (int)ifs.tellg();
        ifs.seekg(0, ifs.beg);
        // read 
        buff = new char[length];
        ifs.read(buff, length);
        // parse
        return LCParser::parseLC(buff);
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

TwoTerminalLinearElement* LCParser::parseLC(char* buff)
{
    auto tokens = LCLexer::lex(buff);
    if (tokens == nullptr)
        return nullptr;
    TwoTerminalLinearElement* element;
    if (*tokens->front() != "{")
        throw std::exception(BRACE_OPEN_EXCEPTION); // although lexer should prevent this from happening
    delete tokens->front();
    tokens->pop(); // '{' popped
    std::string* nextToken = tokens->front();
    if (*nextToken == "Series" || *nextToken == "Parallel")
        element = LCParser::parseCompositeElement(tokens);
    else if (strchr("EJRLC", nextToken->at(0)))
        element = LCParser::parseSingleElement(tokens);
    else throw std::exception(INVALID_IDENTIFIER_EXCEPTION);
    if (*tokens->front() != "}") {
        delete element;
        throw std::exception(BRACE_CLOSE_EXCEPTION);
    }
    delete tokens;
    return element;
}

SingleElement* LCParser::parseSingleElement(std::queue<std::string*>* tokens)
{
    std::string* name = tokens->front();
    tokens->pop();
    if (*tokens->front() != ":")
        throw std::exception(COLON_EXCEPTION);
    delete tokens->front();
    tokens->pop(); // colon popped
    std::string* valString = tokens->front();
    char unit = valString->back();
    if (unit != ')' && (unit < '0' || unit > '9'))
        valString->pop_back();
    std::istringstream valIs(*valString);
    std::complex<double> val;
    valIs >> val;
    //double value = std::stod(*valString); // throws exception if invalid
    delete tokens->front();
    tokens->pop(); // value popped
    switch (name->at(0))
    {
    case 'E':
        return new IdealVoltageSource(*name, val, unit);
    case 'J':
        return new IdealCurrentSource(*name, val, unit);
    case 'R':
        return new Resistor(*name, val.real(), unit);
    case 'L':
        return new Inductor(*name, val.real(), unit);
    case 'C':
        return new Capacitor(*name, val.real(), unit);
    default:
        throw std::exception(INVALID_IDENTIFIER_EXCEPTION);
    }
}

CompositeElement* LCParser::parseCompositeElement(std::queue<std::string*>* tokens)
{
    CompositeElement* composite;
    char type = tokens->front()->at(0);
    delete tokens->front();
    tokens->pop(); // identifier popped

    if (*tokens->front() != ":")
        throw std::exception(COLON_EXCEPTION);
    delete tokens->front();
    tokens->pop(); // ":" popped

    if (*tokens->front() != "[")
        throw std::exception(BRACKET_OPEN_EXCEPTION);
    delete tokens->front();
    tokens->pop(); // "[" popped

    if (type == 'S')
        composite = new InSeries();
    else if (type == 'P') {
        composite = new InParallel();
    }
    else throw std::exception(INVALID_COMPOSITE_EXCEPTION);

    std::string* nextToken = tokens->front();
    while (true) {
        if (*nextToken == "Series" || *nextToken == "Parallel")
            composite->Add(LCParser::parseCompositeElement(tokens));
        else if (strchr("EJRLC", nextToken->at(0)))
            composite->Add(LCParser::parseSingleElement(tokens));
        else throw std::exception(INVALID_IDENTIFIER_EXCEPTION);

        // Element definition popped, expecting comma or closed bracket
        if (*tokens->front() == "]") {
            delete tokens->front();
            tokens->pop();
            break;
        }
        if (*tokens->front() != ";")
            throw std::exception(COMMA_EXCEPTION);
        delete tokens->front();
        tokens->pop(); // Comma popped
        nextToken = tokens->front();
    }
    return composite;
}
