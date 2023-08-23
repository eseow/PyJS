#ifndef OR_EXPR_H
#define OR_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class OrExpr : public Expr
{
public:
    OrExpr(Expr *left, Expr *right);
    std::string toString();
    Expr *left;
    Expr *right;
};
#endif