#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class BinaryExpr : Expr
{
public:
    Expr left;
    Expr right;
    Token binaryOperator;
};
#endif