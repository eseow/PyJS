#include "Statement.h"
#include "StatementVisitor.h"
IfStmt::IfStmt(
    Expr *ifCond,
    std::vector<Stmt *> body,
    std::vector<IfStmt *> elifStmt,
    std::vector<Stmt *> elseBody)
{
    this->ifCond = ifCond;
    this->body = body;
    this->elifStmt = elifStmt;
    this->elseBody = elseBody;
}

std::string IfStmt::toString()
{
    return StatementVisitor::accept(this);
}