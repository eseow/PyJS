#ifndef PARSER_H
#define PARSER_H
#include "Expressions/Expr.h"
class Parser
{
public:
    Expr parseRootExpr();
    Expr parseInlineExpr();
    Expr parseComparsionExpr();
    Expr parseEqualityExpr();
    Expr parseBinaryExpr();
    Expr parseUnaryExpr();
    Expr parseTermExpr();
    Expr parsePrimaryExpr();
    void parse();
};
#endif