#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class UnaryExpr : Expr
{
public:
    Expr body;
    Token unaryOperator;
};
#endif