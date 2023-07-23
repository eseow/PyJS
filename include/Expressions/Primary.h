#ifndef COMPARISON_EXPR_H
#define COMPARISON_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
#include "variant"
#include "map"
enum PrimaryType
{
    PRIMARY_STRING,
    PRIMARY_DOUBLE,
    PRIMARY_INT,
    PRIMARY_BOOLEAN,
    PRIMARY_IDENTIFIER
};
class Primary : public Expr
{
public:
    Primary(PrimaryType type, int value);
    Primary(PrimaryType type, bool value);
    Primary(PrimaryType type, double value);
    Primary(PrimaryType type, string value);
    PrimaryType type;
    std::string toString() override;
    static std::map<PrimaryType, std::string> primaryTypeStrings;
    std::variant<int, std::string, double, bool> value;
};
#endif