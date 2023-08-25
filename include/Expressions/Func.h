#ifndef FUNC_EXPR_H
#define FUNC_EXPR_H
#include "Expressions/Expr.h"
#include "Token.h"
#include "vector"
class FuncExpr : public Expr
{
public:
    FuncExpr(std::vector<Expr *> arguments, Token identifier);
    std::string toString() override;
    std::vector<Expr *> arguments;
    Token identifer;
};
#endif