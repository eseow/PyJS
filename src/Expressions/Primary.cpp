#include "Expressions/Primary.h"
#include "Expressions/Expr.h"
#include "Token.h"
#include "variant"
#include <iostream>
#include "ExpressionVisitor.h"
std::map<PrimaryType, std::string> Primary::primaryTypeStrings = {
    {PrimaryType::PRIMARY_STRING, "STRING"},
    {PrimaryType::PRIMARY_DOUBLE, "DOUBLE"},
    {PrimaryType::PRIMARY_INT, "INT"},
    {PrimaryType::PRIMARY_BOOLEAN, "BOOLEAN"},
    {PrimaryType::PRIMARY_IDENTIFIER, "IDENTIFIER"},
};
Primary::Primary(PrimaryType type, bool value)
{
    this->type = type;
    this->value = value;
};
Primary::Primary(PrimaryType type, double value)
{
    this->type = type;
    this->value = value;
};
Primary::Primary(PrimaryType type, int value)
{
    this->type = type;
    this->value = value;
};
Primary::Primary(PrimaryType type, std::string value)
{
    this->type = type;
    this->value = value;
};
std::string Primary::toString()
{
    return ExpressionVisitor::accept(this);
}