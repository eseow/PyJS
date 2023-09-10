#include "StatementVisitor.h"
#include "boost/format.hpp"
std::string StatementVisitor::accept(IfStmt *stmt)
{
    std::string ifStmt = stmt->ifCond->toString();
    std::string body = "";
    for (int i = 0; i < stmt->body.size(); i++)
    {
        body += "\t" + stmt->body.at(i)->toString() + "\n";
    }
    return str(boost::format("if(%1%){\n%2%}") % ifStmt % body);
}

std::string StatementVisitor::accept(ExprStmt *stmt)
{
    std::string exprString = stmt->expr->toString();
    return str(boost::format("%1%;") % exprString);
}