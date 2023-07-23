#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class UnaryExpr : public Expr
{
public:
    UnaryExpr(Expr * body, Token unaryOperator);
    Expr body;
    Token unaryOperator;
};
#endif