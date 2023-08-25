#include "Expressions/Func.h"
#include "Expressions/Expr.h"
#include "Token.h"
#include "ExpressionVisitor.h"
FuncExpr::FuncExpr(std::vector<Expr *> arguments, Token identifier)
{
    this->identifer = identifier;
    this->arguments = arguments;
};

std::string FuncExpr::toString()
{
    return ExpressionVisitor::accept(this);
}