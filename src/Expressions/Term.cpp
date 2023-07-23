#include "Expressions/Term.h"
#include "Expressions/Expr.h"
TermExpr::TermExpr(Expr *left, Expr *right, Token termOperator)
{
    this->left = left;
    this->right = right;
    this->termOperator = termOperator;
};