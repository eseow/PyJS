#ifndef EQUALITY_H
#define EQUALITY_H
#include "Expressions/Expr.h"
#include "Token.h"
class EqualityExpr : Expr
{
public:
    Expr left;
    Expr right;
    Token equalityOperator;
};
#endif