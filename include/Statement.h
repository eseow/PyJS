#ifndef STATEMENT_H
#define STATEMENT_H
#include "Expressions/Expr.h"
#include <string>
#include <vector>
class Stmt
{
public:
    std::string virtual toJsString() = 0;
};

class IfStmt : public Stmt
{
public:
    IfStmt(
        std::vector<Stmt *> body,
        std::vector<IfStmt *> elifStmt,
        std::vector<Stmt *> elseBody);
    std::string toJsString();
    Expr *ifCond;
    std::vector<Stmt *> body;
    std::vector<IfStmt *> elifStmt;
    std::vector<Stmt *> elseBody;
};

class ExprStmt : public Stmt
{
public:
    ExprStmt(
        Expr *expr);
    std::string toJsString();
    Expr *expr;
};
#endif