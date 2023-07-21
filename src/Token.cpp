#include "../include/Token.h"
#include "../include/TokenType.h"
#include <map>
#include <variant>
#include <iostream>
#include <sstream>

std::map<TokenType, std::string> *Token::tokenTypeMap = new std::map<TokenType, std::string>({// TokenType to string
                                                                                              {TokenType::NEWLINE, "newline"},
                                                                                              {TokenType::PRINT, "print"},
                                                                                              {TokenType::MODULO, "modulo"},
                                                                                              {TokenType::RANGE, "range"},
                                                                                              {TokenType::HASH, "comment"},
                                                                                              {TokenType::TAB, "tab"},
                                                                                              {TokenType::IDENTIFIER, "identifier"},
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
std::map<TokenType, std::string> *Token::tokenLexemeMap = new std::map<TokenType, std::string>({// Literals
                                                                                                {TokenType::NEWLINE, "\n"},
                                                                                                {TokenType::PRINT, "print"},
                                                                                                {TokenType::MODULO, "%"},
                                                                                                {TokenType::RANGE, "range"},
                                                                                                {TokenType::HASH, "#"},
                                                                                                {TokenType::TAB, "\\t"},
                                                                                                {TokenType::IDENTIFIER, "identifier"},
                                                                                                {TokenType::STRING, "string"},
                                                                                                {TokenType::INT, "int"},
                                                                                                {TokenType::DOUBLE, "double"},
                                                                                                {TokenType::BOOL, "bool"},

                                                                                                // Keywords
                                                                                                {TokenType::FALSE, "False"},
                                                                                                {TokenType::NONE, "None"},
                                                                                                {TokenType::TRUE, "True"},
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

                                                                                                // Operators and Delimiters
                                                                                                {TokenType::PLUS, "+"},
                                                                                                {TokenType::MINUS, "-"},
                                                                                                {TokenType::ASTERISK, "*"},
                                                                                                {TokenType::SLASH, "/"},
                                                                                                {TokenType::DOUBLE_SLASH, "//"},
                                                                                                {TokenType::PERCENT, "%"},
                                                                                                {TokenType::DOUBLE_ASTERISK, "**"},
                                                                                                {TokenType::EQUAL, "="},
                                                                                                {TokenType::DOUBLE_EQUAL, "=="},
                                                                                                {TokenType::NOT_EQUAL, "!="},
                                                                                                {TokenType::GREATER, ">"},
                                                                                                {TokenType::GREATER_EQUAL, ">="},
                                                                                                {TokenType::LESS, "<"},
                                                                                                {TokenType::LESS_EQUAL, "<="},
                                                                                                {TokenType::PLUS_EQUAL, "+="},
                                                                                                {TokenType::MINUS_EQUAL, "-="},
                                                                                                {TokenType::ASTERISK_EQUAL, "*="},
                                                                                                {TokenType::SLASH_EQUAL, "/="},
                                                                                                {TokenType::DOUBLE_SLASH_EQUAL, "//="},
                                                                                                {TokenType::PERCENT_EQUAL, "%="},
                                                                                                {TokenType::DOUBLE_ASTERISK_EQUAL, "**="},
                                                                                                {TokenType::VERTICAL_BAR, "|"},
                                                                                                {TokenType::AMPERSAND, "&"},
                                                                                                {TokenType::TILDE, "~"},
                                                                                                {TokenType::CARET, "^"},
                                                                                                {TokenType::RIGHT_SHIFT, ">>"},
                                                                                                {TokenType::LEFT_SHIFT, "<<"},
                                                                                                {TokenType::LEFT_PAREN, "("},
                                                                                                {TokenType::RIGHT_PAREN, ")"},
                                                                                                {TokenType::LEFT_BRACKET, "["},
                                                                                                {TokenType::RIGHT_BRACKET, "]"},
                                                                                                {TokenType::LEFT_BRACE, "{"},
                                                                                                {TokenType::RIGHT_BRACE, "}"},
                                                                                                {TokenType::COMMA, ","},
                                                                                                {TokenType::COLON, ":"},
                                                                                                {TokenType::SEMICOLON, ";"},
                                                                                                {TokenType::ARROW, "->"},
                                                                                                {TokenType::AT, "@"}});
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
    if (type == TokenType::DOUBLE)
    {

        std::ostringstream oss;
        oss << std::fixed << lexeme;

        std::string result = oss.str();
        size_t pos = result.find_last_not_of('0');
        if (pos != std::string::npos && result[pos] == '.')
            pos++;
        result = result.substr(0, pos + 1);

        return "double " + result;
    }
    if (tokenTypeMap->count(type) > 0)
    {
        std::string str = tokenTypeMap->at(type);

        if (str == "string" || str == "comment" || str == "identifier")
        {
            return str + " " + "'" + lexeme + "'";
        }
        return str + " " + lexeme;
    }
    return "No TokenType" + lexeme;
}