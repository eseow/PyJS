#ifndef SCANNER_EXCEPTION
#define SCANNER_EXCEPTION
#include <string>
#include <exception>
class ScannerException : public std::exception
{
public:
    ScannerException(int line, int column, std::string exceptionDetails);
    const char *what();

private:
    int line;
    int column;
    std::string exceptionDetails;
};
#endif