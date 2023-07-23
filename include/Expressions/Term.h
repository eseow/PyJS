#ifndef TERM_EXPR_H
#define TERM_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class TermExpr : public Expr
{
public:
    TermExpr(Expr *left, Expr *right, Token termOperator);
    Expr *left;
    Expr *right;
    Token termOperator;
};
#endif