#ifndef AND_EXPR_H
#define AND_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class AndExpr : public Expr
{
public:
    AndExpr(Expr *left, Expr *right);
    std::string toString() override;
    Expr *left;
    Expr *right;
};
#endif