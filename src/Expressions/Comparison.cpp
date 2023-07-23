#include "Expressions/Comparison.h"
#include "Expressions/Expr.h"
#include "Token.h"
ComparisonExpr::ComparisonExpr(Expr * left, Expr right, Token comparisonOperator)
{
    this->left = left;
    this->right = right;
    this->comparisonOperator = comparisonOperator;
};