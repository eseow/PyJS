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
    Token(TokenType type, string lexeme, int lineNumber, void *literal);
    Token(TokenType type, string lexeme, int lineNumber, string literal);
    Token(TokenType type, string lexeme, int lineNumber, int literal);
    template <typename T>
    T getLiteral();

private:
    TokenType type;
    std::string lexeme;
    int lineNumber;
    std::variant<int, std::string, double, void *> literal;
};

#endif