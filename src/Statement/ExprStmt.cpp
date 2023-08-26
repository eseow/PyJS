#include "Statement.h"
#include "StatementVisitor.h"
ExprStmt::ExprStmt(
    Expr *expr)
{
    this->expr = expr;
}

std::string ExprStmt::toString()
{
    return StatementVisitor::accept(this);
}