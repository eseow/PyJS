#ifndef EQUALITY_H
#define EQUALITY_H
#include "Expressions/Expr.h"
#include "Token.h"
class EqualityExpr : public Expr
{
public:
    EqualityExpr(Expr *left, Expr *right, Token equalityOperator);
    Expr *left;
    Expr *right;
    Token equalityOperator;
};
#endif