#include "Expressions/Factor.h"
#include "Expressions/Expr.h"
#include "Token.h"
FactorExpr::FactorExpr(Expr *left, Expr *right, Token factorOperator)
{
    this->left = left;
    this->right = right;
    this->factorOperator = factorOperator;
};