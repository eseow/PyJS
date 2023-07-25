#ifndef PARSER_H
#define PARSER_H
#include "Expressions/Expr.h"
#include <vector>
#include "Token.h"
class Parser
{
public:
    Parser(std::vector<Token> *tokens);
    void parse();
    std::vector<Expr *> getExprs();

private:
    bool finishedParsing();
    Expr *parseRootExpr();
    Expr *parseInlineExpr();
    Expr *parseComparisonExpr();
    Expr *parseEqualityExpr();
    Expr *parseBinaryExpr();
    Expr *parseUnaryExpr();
    Expr *parseTermExpr();
    Expr *parsePrimaryExpr();
    Token peek();
    bool matchTokenType(TokenType type);
    void advance();
    void consume(TokenType type, std::string errorString);
    std::vector<Token> *tokens;
    int current;
    std::vector<Expr *> exprs;
};
#endif