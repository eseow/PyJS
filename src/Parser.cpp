#include "Parser.h"
#include "Expressions/Expr.h"
#include "Expressions/Inline.h"
#include "Expressions/Comparison.h"
#include "Expressions/Equality.h"
#include "Expressions/Not.h"
#include "Expressions/And.h"
#include "Expressions/Or.h"
#include "Expressions/Unary.h"
#include "Expressions/Factor.h"
#include "Expressions/Term.h"
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
    Expr *if_case = parseComparisonExpr();
    // Expr *if_case = parsePrimaryExpr();
    if (matchTokenType(TokenType::IF))
    {
        Expr *if_conditional = parseComparisonExpr();
        consume(TokenType::ELSE, "In ternary operator, no else " + peek().toString());
        Expr *else_case = parseInlineExpr();
        return new InlineExpr(if_case, if_conditional, else_case);
    }
    return if_case;
}

Expr *Parser::parseComparisonExpr()
{
    Expr *comp = parseEqualityExpr();
    while (matchTokenType(TokenTypeGroups::COMPARISON_TYPES))
    {
        Token token = previous();
        Expr *right = parseEqualityExpr();
        comp = new ComparisonExpr(comp, right, token);
    }
    return comp;
}

Expr *Parser::parseEqualityExpr()
{
    Expr *equality = parseOrExpr();
    while (matchTokenType(TokenTypeGroups::EQUALITY_TYPES))
    {
        Token token = previous();
        Expr *right = parseOrExpr();
        equality = new EqualityExpr(equality, right, token);
    }
    return equality;
}
Expr *Parser::parseOrExpr()
{
    Expr *andExpr = parseAndExpr();
    while (matchTokenType(TokenType::OR))
    {
        Expr *right = parseAndExpr();
        andExpr = new OrExpr(andExpr, right);
    }
    return andExpr;
}
Expr *Parser::parseAndExpr()
{
    Expr *notExpr = parseNotExpr();
    while (matchTokenType(TokenType::AND))
    {
        Expr *right = parseNotExpr();
        notExpr = new AndExpr(notExpr, right);
    }
    return notExpr;
}
Expr *Parser::parseNotExpr()
{
    Expr *termExpr = parseTermExpr();
    while (matchTokenType(TokenType::NOT))
    {
        Token token = previous();
        termExpr = new NotExpr(termExpr);
    }
    return termExpr;
}
Expr *Parser::parseTermExpr()
{
    Expr *term = parseFactorExpr();
    while (matchTokenType(TokenTypeGroups::TERM_TYPES))
    {
        Token token = previous();
        Expr *right = parseFactorExpr();
        term = new TermExpr(term, right, token);
    }
    return term;
}

Expr *Parser::parseFactorExpr()
{
    Expr *factor = parsePrimaryExpr();
    while (matchTokenType(TokenTypeGroups::FACTOR_EXPR))
    {
        Token token = previous();
        Expr *right = parsePrimaryExpr();
        factor = new FactorExpr(factor, right, token);
    }
    return factor;
}
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

Token Parser::previous()
{
    return tokens->at(current - 1);
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

bool Parser::matchTokenType(std::vector<TokenType> types)
{
    if (finishedParsing())
    {
        return false;
    }
    for (int i = 0; i < types.size(); i++)
    {

        if (peek().getTokenType() == types[i])
        {
            advance();
            return true;
        };
    }
    return false;
}

bool Parser::finishedParsing()
{
    return current > (int)tokens->size() - 1;
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

std::string Parser::getExprsString()
{
    std::string str = "";
    for (int i = 0; i < exprs.size(); i++)
    {
        str += exprs[i]->toString();
        if (i != exprs.size() - 1)
        {
            str += "\n";
        }
    }
    return str;
}