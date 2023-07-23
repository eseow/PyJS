#ifndef PARSER_H
#define PARSER_H
#include "Expressions/Expr.h"
#include <vector>
#include "Token.h"
class Parser
{
public:
    Expr *parseRootExpr();
    Expr *parseInlineExpr();
    Expr *parseComparisonExpr();
    Expr *parseEqualityExpr();
    Expr *parseBinaryExpr();
    Expr *parseUnaryExpr();
    Expr *parseTermExpr();
    Expr *parsePrimaryExpr();
    Parser(std::vector<Token> *tokens);
    Token peek();
    bool matchTokenType(TokenType type);
    void advance();
    void parse();
    void consume(TokenType type, std::string errorString);

private:
    std::vector<Token> *tokens;
    int current;
};
#endif