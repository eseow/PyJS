#ifndef FACTOR_EXPR_H
#define FACTOR_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class FactorExpr : public Expr
{
public:
    FactorExpr(Expr *left, Expr *right, Token factorOperator);
    std::string toString();
    Expr *left;
    Expr *right;
    Token factorOperator;
};
#endif