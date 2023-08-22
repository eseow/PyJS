#include "Expressions/Unary.h"
#include "Expressions/Expr.h"
#include "ExpressionVisitor.h"
UnaryExpr::UnaryExpr(Expr *body, Token unaryOperator)
{
    this->body = body;
    this->unaryOperator = unaryOperator;
};

std::string UnaryExpr::toString()
{
    return ExpressionVisitor::accept(this);
}