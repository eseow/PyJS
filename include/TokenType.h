#ifndef TOKEN_TYPE_H
#include <map>
#include <string>
#define TOKEN_TYPE_H

/*

    todo - fill out rest of the python token types
    missing token types
    %s
    is
    None
    continue
    elif

*/

enum TokenType
{

    // Literals.
    IDENTIFIER,
    STRING,
    INT,
    DOUBLE,
    BOOL,

    // Keywords.
    FALSE,
    NONE,
    TRUE,
    AND,
    AS,
    ASSERT,
    ASYNC,
    AWAIT,
    BREAK,
    CLASS,
    CONTINUE,
    DEF,
    DEL,
    ELIF,
    ELSE,
    EXCEPT,
    FINALLY,
    FOR,
    FROM,
    GLOBAL,
    IF,
    IMPORT,
    IN,
    IS,
    LAMBDA,
    NONLOCAL,
    NOT,
    OR,
    PASS,
    RAISE,
    RETURN,
    TRY,
    WHILE,
    WITH,
    YIELD,

    // Operators and Delimiters.
    PLUS,
    MINUS,
    ASTERISK,

    SLASH,
    DOUBLE_SLASH,
    PERCENT,
    DOUBLE_ASTERISK,
    EQUAL,
    DOUBLE_EQUAL,
    NOT_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    PLUS_EQUAL,
    MINUS_EQUAL,
    ASTERISK_EQUAL,
    SLASH_EQUAL,
    DOUBLE_SLASH_EQUAL,
    PERCENT_EQUAL,
    DOUBLE_ASTERISK_EQUAL,
    VERTICAL_BAR,
    AMPERSAND,
    TILDE,
    CARET,
    RIGHT_SHIFT,
    LEFT_SHIFT,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    COLON,
    SEMICOLON,
    ARROW,
    AT
};
#endif
