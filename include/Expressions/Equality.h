#ifndef EQUALITY_H
#define EQUALITY_H
#include "Expressions/Expr.h"
#include "Token.h"
class EqualityExpr : public Expr
{
public:
    EqualityExpr(Expr *left, Expr *right, Token equalityOperator);
    std::string toString() override;
    Expr *left;
    Expr *right;
    Token equalityOperator;
};
#endif