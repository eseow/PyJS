#ifndef FACTOR_EXPR_H
#define FACTOR_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class FactorExpr : Expr
{
public:
    Expr left;
    Expr right;
    Token factorOperator;
};
#endif