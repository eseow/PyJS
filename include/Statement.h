#ifndef STATEMENT_H
#define STATEMENT_H
#include <string>
class Statement
{
public:
    std::string virtual toString();
};

class FunctionStatement : Statement
{
public:
    std::string toString();
};
#endif