#ifndef PARSER_EXCEPTION
#define PARSER_EXCEPTION
#include <string>
#include <exception>
#include "Token.h"
class ParserException : public std::exception
{
public:
    ParserException(int line, int column, std::string exceptionDetails);
    const char *what();

private:
    int line;
    int column;
    std::string exceptionDetails;
};
#endif