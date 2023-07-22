#ifndef INLINE_EXPR_H
#define INLINE_EXPR_H
#include "Expressions/Expr.h"
class InlineExpr : Expr
{
public:
    Expr if_case;
    Expr if_conditional;
    Expr else_case;
};
#endif