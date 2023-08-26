#include "Parser.h"
#include "Expressions/Expr.h"
#include "Expressions/Inline.h"
#include "Expressions/Func.h"
#include "Expressions/Comparison.h"
#include "Expressions/Equality.h"
#include "Expressions/Not.h"
#include "Expressions/And.h"
#include "Expressions/Or.h"
#include "Expressions/Factor.h"
#include "Expressions/Term.h"
#include "Expressions/Primary.h"
#include <vector>
#include "ParserException.h"
#include <iostream>
#include "Token.h"
#include "Statement.h"
Parser::Parser(std::vector<Token> *tokens)
{
    this->current = 0;
    this->tokens = tokens;
    this->bodyDepth = 0;
    this->currentDepth = 0;
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
Stmt *Parser::parseStmt()
{
    if (peekTokenType(TokenType::IF))
    {
        return parseIfStmt();
    }
    else if (peekTokenType(TokenType::DEF))
    {
    }
    else if (peekTokenType(TokenType::IDENTIFIER))
    {
        // function inv, variable set
    }
    else if (peekTokenType(TokenType::ELIF))
    {
        throwParserException("Missing if statement");
    }
    else
    {
        return parseExprStmt();
    }
}

void Parser::clearWhitespace()
{
    int tabs = 0;
    while (peekTokenType(TokenType::TAB) || peekTokenType(TokenType::NEWLINE))
    {
        if (matchTokenType(TokenType::TAB))
        {
            tabs++;
        }
        else
        {
            tabs = 0;
        }
        advance();
    }
    currentDepth = tabs;
    if (currentDepth > bodyDepth)
    {
        throwParserException("Unexpected indentation");
    }
}
void Parser::parseBody(std::vector<Stmt *> *body)
{
    bodyDepth++;
    do
    {
        clearWhitespace();
        if (currentDepth < bodyDepth)
        {
            current -= currentDepth;
            break;
        }
        body->push_back(parseStmt());
    } while (currentDepth == bodyDepth);
    bodyDepth--;
}

IfStmt *Parser::parseIfStmt()
{
    bool isIf;
    if (matchTokenType(TokenType::IF))
    {
        isIf = true;
    }
    else if (matchTokenType(TokenType::ELIF))
    {
        isIf = false;
    }
    Expr *ifCond = parseRootExpr();
    consume(TokenType::COLON, "No : in if statement");
    std::vector<Stmt *> body;
    std::vector<IfStmt *> elifStmts;
    std::vector<Stmt *> elseBody;
    parseBody(&body);
    if (isIf)
    {
        if (currentDepth == bodyDepth)
        {
            while (peekTokenType(TokenType::ELIF))
            {
                consume(TokenType::COLON, "No : in elif statement");
                elifStmts.push_back(parseIfStmt());
            }
        }
        if (currentDepth == bodyDepth)
        {

            if (matchTokenType(TokenType::ELSE))
            {
                consume(TokenType::COLON, "No : in else statement");
                parseBody(&elseBody);
                if (elseBody.size() == 0)
                {
                    throwParserException("Empty body for else statement");
                }
            }
        }
    }
    if (body.size() == 0)
    {
        throwParserException("Empty body for if statement");
    }
    return new IfStmt(body, elifStmts, elseBody);
}

Stmt *Parser::parseExprStmt()
{
    return new ExprStmt(parseRootExpr());
}
Expr *Parser::parseRootExpr()
{

    if (matchTokenType(TokenType::NEWLINE))
    {
        return nullptr;
    }
    else if (matchTokenType(TokenType::HASH))
    {
        return nullptr;
    }
    return parseFuncExpr();
};
void Parser::throwParserException(std::string s)
{

    Token token = peek();
    TokenType type = token.getTokenType();
    throw ParserException(token.getLine(), token.getColumn(), s + " " + token.toString());
}

Expr *Parser::parseFuncExpr()
{
    Expr *inlineExpr;
    if (matchTokenType(TokenType::IDENTIFIER))
    {
        Token identifier = previous();
        if (matchTokenType(TokenType::LEFT_PAREN))
        {
            std::vector<Expr *> args = std::vector<Expr *>();
            if (matchTokenType(TokenType::RIGHT_PAREN))
            {
                return new FuncExpr(args, identifier);
            }
            args.push_back(parseFuncExpr());
            while (matchTokenType(TokenType::COMMA))
            {
                args.push_back(parseFuncExpr());
            }
            if (matchTokenType(TokenType::RIGHT_PAREN))
            {
                return new FuncExpr(args, identifier);
            }
            else
            {
                throwParserException("Missing matching ) for func expr");
            }
        }
    }
    return parseInlineExpr();
}
Expr *Parser::parseInlineExpr()
{
    Expr *if_case = parseOrExpr();
    // Expr *if_case = parsePrimaryExpr();
    if (matchTokenType(TokenType::IF))
    {
        Expr *if_conditional = parseOrExpr();
        consume(TokenType::ELSE, "In ternary operator, no else " + peek().toString());
        Expr *else_case = parseInlineExpr();
        return new InlineExpr(if_case, if_conditional, else_case);
    }
    return if_case;
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
    if (matchTokenType(TokenType::NOT))
    {
        return new NotExpr(parseNotExpr());
    }
    return parseComparisonExpr();
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
    Expr *equality = parseTermExpr();
    while (matchTokenType(TokenTypeGroups::EQUALITY_TYPES))
    {
        Token token = previous();
        Expr *right = parseTermExpr();
        equality = new EqualityExpr(equality, right, token);
    }
    return equality;
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
    while (matchTokenType(TokenTypeGroups::FACTOR_TYPES))
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

bool Parser::peekTokenType(TokenType type)
{
    if (finishedParsing())
    {
        return false;
    }
    if (peek().getTokenType() == type)
    {
        return true;
    };
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

void Parser::consume(std::vector<TokenType> types, std::string errorString)
{
    if (!matchTokenType(types))
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