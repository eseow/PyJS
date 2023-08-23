#ifndef NOT_EXPR_H
#define NOT_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class NotExpr : public Expr
{
public:
    NotExpr(Expr *body);
    std::string toString();
    Expr *body;
};
#endif