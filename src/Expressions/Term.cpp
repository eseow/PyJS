#include "Expressions/Term.h"
#include "Expressions/Expr.h"
#include "ExpressionVisitor.h"
TermExpr::TermExpr(Expr *left, Expr *right, Token termOperator)
{
    this->left = left;
    this->right = right;
    this->termOperator = termOperator;
};

std::string TermExpr::toString()
{
    return ExpressionVisitor::accept(this);
}