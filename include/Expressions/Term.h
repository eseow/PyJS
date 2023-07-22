#ifndef TERM_EXPR_H
#define TERM_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class TermExpr : Expr
{
public:
    Expr left;
    Expr right;
    Token termOperator;
};
#endif