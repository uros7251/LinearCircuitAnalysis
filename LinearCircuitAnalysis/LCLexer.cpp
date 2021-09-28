#include "LCLexer.h"

std::queue<std::string*>* LCLexer::lex(const char* buff)
{
    while (*buff != '\0' && *buff != '{')
        buff++;
    if (*buff == '\0')
        return nullptr;
    auto tokens = new std::queue<std::string*>();
    std::string* token;
    while (*buff != '\0') {
        skipBlanks(&buff);
        if ((token = readDelim(&buff)) ||
            (token = readString(&buff)) ||
            (token = readNumber(&buff))) {
            tokens->push(token);
            continue;
        }
    }
    return tokens;
}

void LCLexer::skipBlanks(const char** buff)
{
    static char blanks[] = " \r\n\t";
    while (**buff != '\0' && strchr(blanks, **buff) != nullptr)
        (*buff)++;
}

std::string* LCLexer::readDelim(const char** buff)
{
    static char delims[] = "{}[]:;";
    std::string* token = nullptr;
    char* ch = strchr(delims, **buff);
    if (ch != nullptr) {
        token = new std::string();
        token->append(1, *ch);
        (*buff)++;
    }
    return token;
}

std::string* LCLexer::readString(const char** buff)
{
    if (**buff != '\"')
        return nullptr;
    std::string* token = new std::string();
    (*buff)++; // skip opening quote
    do {
        token->append(1, *((*buff)++));
    } while (**buff != '\0' && **buff != '\"');
    (*buff)++; // skip closing quote
    return token;
}

std::string* LCLexer::readNumber(const char** buff)
{
    static char delims[] = " \r\n\t;]}";
    std::string* token = new std::string();
    do {
        token->append(1, *((*buff)++));
    } while (**buff != '\0' && !strchr(delims, **buff));
    return token;
}
