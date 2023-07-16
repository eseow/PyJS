#include "../include/Token.h"
#include "../include/TokenType.h"
#include <map>
#include <variant>
#include <iostream>

std::map<TokenType, std::string> *Token::tokenTypeMap = new std::map<TokenType, std::string>({{TokenType::IDENTIFIER, "identifier"},
                                                                                              {TokenType::STRING, "string"},
                                                                                              {TokenType::INT, "int"},
                                                                                              {TokenType::DOUBLE, "double"},
                                                                                              {TokenType::BOOL, "bool"},
                                                                                              {TokenType::FALSE, "false"},
                                                                                              {TokenType::NONE, "none"},
                                                                                              {TokenType::TRUE, "true"},
                                                                                              {TokenType::AND, "and"},
                                                                                              {TokenType::AS, "as"},
                                                                                              {TokenType::ASSERT, "assert"},
                                                                                              {TokenType::ASYNC, "async"},
                                                                                              {TokenType::AWAIT, "await"},
                                                                                              {TokenType::BREAK, "break"},
                                                                                              {TokenType::CLASS, "class"},
                                                                                              {TokenType::CONTINUE, "continue"},
                                                                                              {TokenType::DEF, "def"},
                                                                                              {TokenType::DEL, "del"},
                                                                                              {TokenType::ELIF, "elif"},
                                                                                              {TokenType::ELSE, "else"},
                                                                                              {TokenType::EXCEPT, "except"},
                                                                                              {TokenType::FINALLY, "finally"},
                                                                                              {TokenType::FOR, "for"},
                                                                                              {TokenType::FROM, "from"},
                                                                                              {TokenType::GLOBAL, "global"},
                                                                                              {TokenType::IF, "if"},
                                                                                              {TokenType::IMPORT, "import"},
                                                                                              {TokenType::IN, "in"},
                                                                                              {TokenType::IS, "is"},
                                                                                              {TokenType::LAMBDA, "lambda"},
                                                                                              {TokenType::NONLOCAL, "nonlocal"},
                                                                                              {TokenType::NOT, "not"},
                                                                                              {TokenType::OR, "or"},
                                                                                              {TokenType::PASS, "pass"},
                                                                                              {TokenType::RAISE, "raise"},
                                                                                              {TokenType::RETURN, "return"},
                                                                                              {TokenType::TRY, "try"},
                                                                                              {TokenType::WHILE, "while"},
                                                                                              {TokenType::WITH, "with"},
                                                                                              {TokenType::YIELD, "yield"},
                                                                                              {TokenType::PLUS, "plus"},
                                                                                              {TokenType::MINUS, "minus"},
                                                                                              {TokenType::ASTERISK, "asterisk"},
                                                                                              {TokenType::SLASH, "slash"},
                                                                                              {TokenType::DOUBLE_SLASH, "double_slash"},
                                                                                              {TokenType::PERCENT, "percent"},
                                                                                              {TokenType::DOUBLE_ASTERISK, "double_asterisk"},
                                                                                              {TokenType::EQUAL, "equal"},
                                                                                              {TokenType::DOUBLE_EQUAL, "double_equal"},
                                                                                              {TokenType::NOT_EQUAL, "not_equal"},
                                                                                              {TokenType::GREATER, "greater"},
                                                                                              {TokenType::GREATER_EQUAL, "greater_equal"},
                                                                                              {TokenType::LESS, "less"},
                                                                                              {TokenType::LESS_EQUAL, "less_equal"},
                                                                                              {TokenType::PLUS_EQUAL, "plus_equal"},
                                                                                              {TokenType::MINUS_EQUAL, "minus_equal"},
                                                                                              {TokenType::ASTERISK_EQUAL, "asterisk_equal"},
                                                                                              {TokenType::SLASH_EQUAL, "slash_equal"},
                                                                                              {TokenType::DOUBLE_SLASH_EQUAL, "double_slash_equal"},
                                                                                              {TokenType::PERCENT_EQUAL, "percent_equal"},
                                                                                              {TokenType::DOUBLE_ASTERISK_EQUAL, "double_asterisk_equal"},
                                                                                              {TokenType::VERTICAL_BAR, "vertical_bar"},
                                                                                              {TokenType::AMPERSAND, "ampersand"},
                                                                                              {TokenType::TILDE, "tilde"},
                                                                                              {TokenType::CARET, "caret"},
                                                                                              {TokenType::RIGHT_SHIFT, "right_shift"},
                                                                                              {TokenType::LEFT_SHIFT, "left_shift"},
                                                                                              {TokenType::LEFT_PAREN, "left_paren"},
                                                                                              {TokenType::RIGHT_PAREN, "right_paren"},
                                                                                              {TokenType::LEFT_BRACKET, "left_bracket"},
                                                                                              {TokenType::RIGHT_BRACKET, "right_bracket"},
                                                                                              {TokenType::LEFT_BRACE, "left_brace"},
                                                                                              {TokenType::RIGHT_BRACE, "right_brace"},
                                                                                              {TokenType::COMMA, "comma"},
                                                                                              {TokenType::COLON, "colon"},
                                                                                              {TokenType::SEMICOLON, "semicolon"},
                                                                                              {TokenType::ARROW, "arrow"},
                                                                                              {TokenType::AT, "at"}});
Token::Token(TokenType type, std::string lexeme, int lineNumber, void *literal)
{
    this->type = type;
    this->lexeme = lexeme;
    this->lineNumber = lineNumber;
    this->literal = literal;
}
Token::Token(TokenType type, std::string lexeme, int lineNumber, string literal)
{
    this->type = type;
    this->lexeme = lexeme;
    this->lineNumber = lineNumber;
    this->literal = literal;
}
Token::Token(TokenType type, std::string lexeme, int lineNumber, int literal)
{
    this->type = type;
    this->lexeme = lexeme;
    this->lineNumber = lineNumber;
    this->literal = literal;
}
template <typename T>
T Token::getLiteral()
{
    return std::get<T>(literal);
}
std::string Token::toString()
{
    if (tokenTypeMap->count(type) > 0)
    {
        std::string str = tokenTypeMap->at(type);
        return str + " " + lexeme;
    }
    return "No TokenType" + lexeme;
}