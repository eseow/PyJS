#ifndef PARSER_H
#define PARSER_H
#include "Expressions/Expr.h"
#include <vector>
#include "Token.h"
class Parser
{
public:
    Parser() {}
    Parser(std::vector<Token> *tokens);
    virtual void parse();
    virtual std::string getExprsString();

private:
    bool finishedParsing();
    Expr *parseRootExpr();
    Expr *parseInlineExpr();
    Expr *parseComparisonExpr();
    Expr *parseEqualityExpr();
    Expr *parseOrExpr();
    Expr *parseAndExpr();
    Expr *parseNotExpr();
    Expr *parseTermExpr();
    Expr *parseFactorExpr();
    Expr *parsePrimaryExpr();
    Token peek();
    Token previous();
    bool matchTokenType(TokenType type);
    bool matchTokenType(std::vector<TokenType> type);
    void advance();
    void consume(TokenType type, std::string errorString);
    std::vector<Token> *tokens;
    int current;
    std::vector<Expr *> exprs;
};
#endif