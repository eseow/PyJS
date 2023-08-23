#include "Expressions/Or.h"
#include "Expressions/Expr.h"
#include "Token.h"
#include "ExpressionVisitor.h"
OrExpr::OrExpr(Expr *left, Expr *right)
{
    this->left = left;
    this->right = right;
};

std::string OrExpr::toString()
{
    return ExpressionVisitor::accept(this);
}