#include "ScannerException.h"
#include <iostream>
#include <string>

ScannerException::ScannerException(int line, int column, std::string exceptionDetails)
{
    this->line = line;
    this->column = column;
    this->exceptionDetails = exceptionDetails;
}

const char *ScannerException::what()
{
    std::string str = exceptionDetails + " on line " + std::to_string(line) + ":" + std::to_string(column);
    return str.c_str();
}
