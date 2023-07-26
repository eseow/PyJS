#ifndef COMPARISON_EXPR_H
#define COMPARISON_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
class ComparisonExpr : public Expr
{
public:
    ComparisonExpr(Expr *left, Expr *right, Token comparisonOperator);
    Expr *left;
    Expr *right;
    Token comparisonOperator;
    std::string toString() override;
};
#endif