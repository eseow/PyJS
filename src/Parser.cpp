#include "Parser.h"
#include "Expressions/Expr.h"
#include "Expressions/Inline.h"
#include "Expressions/Primary.h"
#include "Expressions/Comparison.h"
#include <vector>
#include "ParserException.h"
#include <iostream>
#include "Token.h"

Parser::Parser(std::vector<Token> *tokens)
{
    this->current = 0;
    this->tokens = tokens;
}
void Parser::parse()
{
    while (!finishedParsing())
    {
        try
        {
            Expr *expr = parseRootExpr();
            if (expr != nullptr)
            {
                exprs.push_back(expr);
            }
        }
        catch (ParserException &parserException)
        {
            std::cout << parserException.what();
        };
        advance();
    }
}
Expr *Parser::parseRootExpr()
{

    if (matchTokenType(TokenType::NEWLINE))
    {
        return nullptr;
    }
    return parseInlineExpr();
};

Expr *Parser::parseInlineExpr()
{
    // Expr* if_case = parseComparisonExpr();
    Expr *if_case = parsePrimaryExpr();
    if (matchTokenType(TokenType::IF))
    {
        Expr *if_conditional = parsePrimaryExpr();
        consume(TokenType::ELSE, "In ternary operator, no else " + peek().toString());
        Expr *else_case = parseInlineExpr();
        return new InlineExpr(if_case, if_conditional, else_case);
    }
    return if_case;
}

/*
Expr *Parser::parseComparisonExpr()
{
    Expr *left = parseComparisonExpr();
    TokenType types[4] = {
        TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS_EQUAL, TokenType::LESS};
    for (int i = 0; i < 4; i++)
    {
        Token token = peek();
        if (matchTokenType(types[i]))
        {
            Expr *right = parseEqualityExpr();
            return new ComparisonExpr(left, right, token);
        }
    }
    return nullptr;
}
*/

Expr *Parser::parsePrimaryExpr()
{
    Token token = peek();
    Primary *primary;
    TokenType type = token.getTokenType();
    switch (type)
    {
    case TokenType::STRING:
        primary = new Primary(PrimaryType::PRIMARY_STRING, token.getLiteral<std::string>());
        break;
    case TokenType::IDENTIFIER:
        primary = new Primary(PrimaryType::PRIMARY_IDENTIFIER, token.getLiteral<std::string>());
        break;
    case TokenType::INT:
        primary = new Primary(PrimaryType::PRIMARY_INT, token.getLiteral<int>());
        break;
    case TokenType::DOUBLE:
        primary = new Primary(PrimaryType::PRIMARY_DOUBLE, token.getLiteral<double>());
        break;
    case TokenType::BOOL:
        primary = new Primary(PrimaryType::PRIMARY_BOOLEAN, token.getLiteral<bool>());
        break;
    default:
        throw ParserException(token.getLine(), token.getColumn(), "Invalid primary expr for token " + token.toString());
    }
    advance();
    return primary;
}

Token Parser::peek()
{
    return tokens->at(current);
}

bool Parser::matchTokenType(TokenType type)
{
    if (finishedParsing())
    {
        return false;
    }
    if (peek().getTokenType() == type)
    {
        advance();
        return true;
    };
    return false;
}

bool Parser::finishedParsing()
{
    return current >= (int)tokens->size() - 1;
}

void Parser::consume(TokenType type, std::string errorString)
{
    if (!matchTokenType(type))
    {
        Token token = peek();
        throw ParserException(token.getLine(), token.getColumn(), errorString);
    }
}
void Parser::advance()
{
    current++;
}

std::vector<Expr *> Parser::getExprs()
{
    return exprs;
}
