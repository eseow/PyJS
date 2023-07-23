#ifndef TOKEN_H
#define TOKEN_H
#include "./TokenType.h"
#include <iostream>
#include <variant>
using std::string;

class Token
{
public:
    static std::map<TokenType, std::string> *tokenTypeMap;
    static std::map<TokenType, std::string> *tokenLexemeMap;
    string toString();
    Token();
    Token(TokenType type, string lexeme, int lineNumber, int column, void *literal);
    Token(TokenType type, string lexeme, int lineNumber, int column, string literal);
    Token(TokenType type, string lexeme, int lineNumber, int column, int literal);
    template <typename T>
    T getLiteral();
    TokenType getTokenType();
    int getLine();
    int getColumn();

private:
    TokenType type;
    std::string lexeme;
    int lineNumber;
    int column;
    std::variant<int, std::string, double, void *> literal;
};

#endif