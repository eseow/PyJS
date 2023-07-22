#ifndef COMPARISON_EXPR_H
#define COMPARISON_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
enum PrimaryType
{
    STRING,
    NUMBER,
    BOOLEAN,
    IDENTIFIER
};
class Primary : Expr
{
public:
    PrimaryType type;
    std::variant<int, std::string, double, bool> value;
};
#endif