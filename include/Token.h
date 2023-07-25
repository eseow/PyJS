#ifndef TOKEN_H
#define TOKEN_H
#include "./TokenType.h"
#include <iostream>
#include <variant>
#include <string>

class Token
{
public:
    static std::map<TokenType, std::string> *tokenTypeMap;
    static std::map<TokenType, std::string> *tokenLexemeMap;
    std::string toString();
    Token();
    Token(TokenType type, std::string lexeme, int lineNumber, int column, bool literal);
    Token(TokenType type, std::string lexeme, int lineNumber, int column, double literal);
    Token(TokenType type, std::string lexeme, int lineNumber, int column, std::string literal);
    Token(TokenType type, std::string lexeme, int lineNumber, int column, int literal);
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
    std::variant<int, std::string, double, bool> literal;
};

#endif