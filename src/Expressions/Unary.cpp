#include "Expressions/Unary.h"
#include "Expressions/Expr.h"
UnaryExpr::UnaryExpr(Expr * body, Token unaryOperator)
{
    this->body = body;
    this->unaryOperator = unaryOperator;
};