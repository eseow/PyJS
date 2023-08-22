#include "Expressions/Binary.h"
#include "Expressions/Expr.h"
#include "Token.h"
#include "ExpressionVisitor.h"
BinaryExpr::BinaryExpr(Expr *left, Expr *right, Token binaryOperator)
{
    this->left = left;
    this->right = right;
    this->binaryOperator = binaryOperator;
};

std::string BinaryExpr::toString()
{
    return ExpressionVisitor::accept(this);
}