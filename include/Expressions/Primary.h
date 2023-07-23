#ifndef COMPARISON_EXPR_H
#define COMPARISON_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
#include "variant"
enum PrimaryType
{
    STRING,
    NUMBER,
    BOOLEAN,
    IDENTIFIER
};
class Primary : public Expr
{
public:
    Primary(PrimaryType type, int value);
    Primary(PrimaryType type, bool value);
    Primary(PrimaryType type, double value);
    Primary(PrimaryType type, string value);
    PrimaryType type;
    std::variant<int, std::string, double, bool> value;
};
#endif