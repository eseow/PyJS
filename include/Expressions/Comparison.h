#ifndef COMPARISON_EXPR_H
#define COMPARISON_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class ComparisonExpr : Expr
{
public:
    Expr left;
    Expr right;
    Token comparisonOperator;
};
#endif