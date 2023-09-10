#ifndef STATEMENT_H
#define STATEMENT_H
#include "Expressions/Expr.h"
#include <string>
#include <vector>
class Stmt
{
public:
    std::string virtual toString() = 0;
};

class IfStmt : public Stmt
{
public:
    IfStmt(
        Expr *ifCond,
        std::vector<Stmt *> body,
        std::vector<IfStmt *> elifStmt,
        std::vector<Stmt *> elseBody);
    std::string toString();
    Expr *ifCond;
    std::vector<Stmt *> body;
    std::vector<IfStmt *> elifStmt;
    std::vector<Stmt *> elseBody;
};

class ExprStmt : public Stmt
{
public:
    ExprStmt(Expr *expr);
    std::string toString();
    Expr *expr;
};
#endif