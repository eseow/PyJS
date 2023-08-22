#include "Expressions/Equality.h"
#include "Expressions/Expr.h"
#include "ExpressionVisitor.h"
#include "Token.h"
EqualityExpr::EqualityExpr(Expr *left, Expr *right, Token equalityOperator)
{
    this->left = left;
    this->right = right;
    this->equalityOperator = equalityOperator;
};

std::string EqualityExpr::toString()
{
    return ExpressionVisitor::accept(this);
}