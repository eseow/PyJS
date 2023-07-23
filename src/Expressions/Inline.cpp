#include "Expressions/Inline.h"
#include "Expressions/Expr.h"
#include "Token.h"
InlineExpr::InlineExpr(Expr * if_case, Expr if_conditional, Expr else_case)
{
    this->if_case = if_case;
    this->if_conditional = if_conditional;
    this->else_case = else_case;
};