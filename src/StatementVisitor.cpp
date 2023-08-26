#include "StatementVisitor.h"
#include "boost/format.hpp"
std::string StatementVisitor::accept(IfStmt *stmt)
{
}

std::string StatementVisitor::accept(ExprStmt *stmt)
{
    std::string exprString = stmt->expr->toString();
    return str(boost::format("(EXPR_STMT (%1%))") % exprString);
}