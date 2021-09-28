#pragma once
#include<queue>
#include<string>
class LCLexer
{
public:
	static std::queue<std::string*>* lex(const char* buff);
private:
	static void skipBlanks(const char** buff);
	static std::string* readDelim(const char** buff);
	static std::string* readString(const char** buff);
	static std::string* readNumber(const char** buff);
};

