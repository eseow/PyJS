#include "Expressions/Primary.h"
#include "Expressions/Expr.h"
#include "Token.h"
#include "variant"
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
Primary::Primary(PrimaryType type, string value)
{
    this->type = type;
    this->value = value;
};
