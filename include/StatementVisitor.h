#ifndef STATEMENT_VISITOR_H
#include "Statement.h"
#define STATEMENT_VISITOR_H
class StatementVisitor
{
public:
    static std::string accept(IfStmt *stmt);
    static std::string accept(ExprStmt *stmt);
};
#endif