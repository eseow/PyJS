#ifndef INLINE_EXPR_H
#define INLINE_EXPR_H
#include "Expressions/Expr.h"
class InlineExpr : public Expr
{
public:
    InlineExpr(Expr *if_case, Expr *if_conditional, Expr *else_case);
    Expr *if_case;
    Expr *if_conditional;
    Expr *else_case;
    std::string toString() override;
};
#endif