#include "Expressions/And.h"
#include "Expressions/Expr.h"
#include "Token.h"
#include "ExpressionVisitor.h"
AndExpr::AndExpr(Expr *left, Expr *right)
{
    this->left = left;
    this->right = right;
};

std::string AndExpr::toString()
{
    return ExpressionVisitor::accept(this);
}