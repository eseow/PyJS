#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class BinaryExpr : public Expr
{
public:
    BinaryExpr(Expr *left, Expr *right, Token binaryOperator);
    Expr *left;
    Expr *right;
    Token binaryOperator;
};
#endif