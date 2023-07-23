#include "Expressions/Binary.h"
#include "Expressions/Expr.h"
#include "Token.h"
BinaryExpr::BinaryExpr(Expr *left, Expr *right, Token binaryOperator)
{
    this->left = left;
    this->right = right;
    this->binaryOperator = binaryOperator;
};