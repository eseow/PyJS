#include "ParserException.h"
#include <iostream>
#include <string>

ParserException::ParserException(Token token, std::string exceptionDetails)
{
    this->exceptionDetails = exceptionDetails;
    this->token = token;
}

const char *ParserException::what()
{
    std::cout << exceptionDetails;
}
