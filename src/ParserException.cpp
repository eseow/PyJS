#include "ParserException.h"
#include <iostream>
#include <string>

ParserException::ParserException(int line, int column, std::string exceptionDetails)
{
    this->exceptionDetails = exceptionDetails;
    this->line = line;
    this->column = column;
}

const char *ParserException::what()
{
    return exceptionDetails.c_str();
}
