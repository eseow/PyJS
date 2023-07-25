#include "Parser.h"
#include "Expressions/Expr.h"
#include "Expressions/Inline.h"
#include "Expressions/Primary.h"
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
    while (current < (int)tokens->size())
    {
        try
        {
            Expr *expr = parseRootExpr();
            exprs.push_back(expr);
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

    return parseInlineExpr();
};

Expr *Parser::parseInlineExpr()
{
    // Expr* if_case = parseComparisonExpr();
    Expr *if_case = parsePrimaryExpr();
    if (matchTokenType(TokenType::IF))
    {
        Expr *if_conditional = parsePrimaryExpr();
        Token token = peek();
        consume(TokenType::ELSE, "In ternary operator, no else");
        Expr *else_case = parseInlineExpr();
        return new InlineExpr(if_case, if_conditional, else_case);
    }
    return if_case;
}

Expr *Parser::parsePrimaryExpr()
{
    Token token = peek();
    advance();
    TokenType type = token.getTokenType();
    switch (type)
    {
    case TokenType::STRING:
        return new Primary(PrimaryType::PRIMARY_STRING, token.getLiteral<std::string>());
    case TokenType::IDENTIFIER:
        return new Primary(PrimaryType::PRIMARY_IDENTIFIER, token.getLiteral<std::string>());
    case TokenType::INT:
        return new Primary(PrimaryType::PRIMARY_DOUBLE, token.getLiteral<double>());
    case TokenType::DOUBLE:
        return new Primary(PrimaryType::PRIMARY_INT, token.getLiteral<int>());
    case TokenType::BOOL:
        return new Primary(PrimaryType::PRIMARY_BOOLEAN, token.getLiteral<bool>());
    default:
        throw ParserException(token.getLine(), token.getColumn(), "Invalid primary expr for token" + token.toString());
    }
}

Token Parser::peek()
{
    return tokens->at(current);
}

bool Parser::matchTokenType(TokenType type)
{
    return peek().getTokenType() == type;
}

Expr *Parser::parseComparisonExpr()
{
    return nullptr;
}

void Parser::consume(TokenType type, std::string errorString)
{
    if (matchTokenType(type) != type)
    {
        Token token = peek();
        throw ParserException(token.getLine(), token.getColumn(), errorString);
    }
    advance();
}
void Parser::advance()
{
    current++;
}

std::vector<Expr *> Parser::getExprs()
{
    return exprs;
}