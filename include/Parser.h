#ifndef PARSER_H
#define PARSER_H
#include "Expressions/Expr.h"
#include "Statement.h"
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
    static int bodyDepth;
    static int currentDepth;
    Stmt *parseStmt();
    IfStmt *parseIfStmt();
    Stmt *parseExprStmt();
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
    Expr *parseFuncExpr();
    int removeWhiteSpace();
    void clearWhitespace();
    void parseBody(std::vector<Stmt *> *body);
    Token peek();
    Token previous();
    void throwParserException(std::string s);
    bool matchTokenType(TokenType type);
    bool matchTokenType(std::vector<TokenType> type);
    bool peekTokenType(TokenType type);
    void advance();
    void consume(TokenType type, std::string errorString);
    void consume(std::vector<TokenType> type, std::string errorString);
    std::vector<Token> *tokens;
    int current;
    std::vector<Expr *> exprs;
};
#endif