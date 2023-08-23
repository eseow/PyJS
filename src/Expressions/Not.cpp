#include "Expressions/Not.h"
#include "Expressions/Expr.h"
#include "ExpressionVisitor.h"
NotExpr::NotExpr(Expr *body)
{
    this->body = body;
};

std::string NotExpr::toString()
{
    return ExpressionVisitor::accept(this);
}