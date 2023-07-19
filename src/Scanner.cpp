#include "../include/Scanner.h"
#include "../include/TokenType.h"
#include "../include/ScannerException.h"
#include <regex>
#include <iostream>
using std::string;

char const EOF_CHARACTER = '\0';
string ltrim(const std::string &s)
{
    return std::regex_replace(s, std::regex("^\\s+"), string(""));
}

string rtrim(const std::string &s)
{
    return std::regex_replace(s, std::regex("\\s+$"), string(""));
}

string trim(const std::string &s)
{
    return ltrim(rtrim(s));
}
bool isNumerical(char c)
{
    std::string value(1, c);
    std::regex pattern("^[0-9.]$");
    return std::regex_match(value, pattern);
}
bool isValidVariable(char c)
{
    std::string str(1, c);
    std::regex pattern("^[a-zA-Z_][a-zA-Z0-9_]*$");
    return std::regex_match(str, pattern);
}

Scanner::Scanner(std::ifstream *file)
{
    this->current = 0;
    this->start = 0;
    this->line = 0;
    initFileContents(file);
    this->tokens = new std::vector<Token>();
    this->lexemeLookUp = new std::map<TokenType, std::string>({// Literals
                                                               {TokenType::TAB, "tab"},
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
    this->reverseLexemeLookUp = new std::map<std::string, TokenType>();
    for (const auto &entry : *(this->lexemeLookUp))
    {
        (*this->reverseLexemeLookUp)[entry.second] = entry.first;
    }
}
void Scanner::initFileContents(std::ifstream *file)
{
    file->seekg(0, std::ios_base::end);
    int lengthOfFile = file->tellg();
    this->lengthOfFile = lengthOfFile;
    file->seekg(0, std::ios_base::beg);
    charArray = (char *)malloc(lengthOfFile);
    file->read(charArray, lengthOfFile);
    file->close();
    this->fileContents = string(charArray, lengthOfFile) + '\0';
}
char Scanner::peek()
{
    if (current >= lengthOfFile)
    {
        return EOF_CHARACTER;
    }
    return (fileContents.at(current));
}
char Scanner::peekNext()
{
    if (current + 1 >= lengthOfFile)
    {
        return EOF_CHARACTER;
    }
    return (fileContents.at(current + 1));
}
bool Scanner::matchNext(char matching)
{
    if (peekNext() == matching)
    {
        advance();
        return true;
    }
    return false;
}
void Scanner::consumeToken()
{
    switch (peek())
    {
    case '\t':
        addToken(TokenType::TAB);
        break;
    case '+':
        if (matchNext('='))
        {
            addToken(TokenType::PLUS_EQUAL);
        }
        else
        {
            addToken(TokenType::PLUS);
        }
        break;
    case '-':
        if (matchNext('>'))
        {
            addToken(TokenType::ARROW);
        }
        else if (matchNext('='))
        {
            addToken(TokenType::MINUS_EQUAL);
        }
        else
        {
            addToken(TokenType::MINUS);
        }
        break;
    case '*':
        if (matchNext('='))
        {
            addToken(TokenType::ASTERISK_EQUAL);
        }
        else if (matchNext('*'))
        {
            if (matchNext('='))
            {
                addToken(TokenType::DOUBLE_ASTERISK_EQUAL);
            }
            else
            {
                addToken(TokenType::DOUBLE_ASTERISK);
            }
        }
        else
        {
            addToken(TokenType::ASTERISK);
        }
        break;
    case '/':
        if (matchNext('='))
        {
            addToken(TokenType::SLASH_EQUAL);
        }
        else if (matchNext('/'))
        {
            addToken(TokenType::DOUBLE_SLASH);
        }
        else
        {
            addToken(TokenType::SLASH);
        }
        break;
    case '%':
        if (matchNext('='))
        {
            addToken(TokenType::PERCENT_EQUAL);
        }
        else
        {
            addToken(TokenType::PERCENT);
        }
        break;
    case '=':
        if (matchNext('='))
        {
            addToken(TokenType::DOUBLE_EQUAL);
        }
        else
        {
            addToken(TokenType::EQUAL);
        }
        break;
    case '!':
        if (matchNext('='))
        {
            addToken(TokenType::NOT_EQUAL);
        }
        else
        {
            addToken(TokenType::NOT);
        }
        break;
    case '>':
        if (matchNext('='))
        {
            addToken(TokenType::GREATER_EQUAL);
        }
        else if (matchNext('>'))
        {
            addToken(TokenType::RIGHT_SHIFT);
        }
        else
        {
            addToken(TokenType::GREATER);
        }
        break;
    case '<':
        if (matchNext('='))
        {
            addToken(TokenType::LESS_EQUAL);
        }
        else if (matchNext('<'))
        {
            addToken(TokenType::LEFT_SHIFT);
        }
        else
        {
            addToken(TokenType::LESS);
        }
        break;
    case '|':
        addToken(TokenType::VERTICAL_BAR);
        break;
    case '&':
        addToken(TokenType::AMPERSAND);
        break;
    case '~':
        addToken(TokenType::TILDE);
        break;
    case '^':
        addToken(TokenType::CARET);
        break;
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '[':
        addToken(TokenType::LEFT_BRACKET);
        break;
    case ']':
        addToken(TokenType::RIGHT_BRACKET);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case ':':
        addToken(TokenType::COLON);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case ' ':
        break;
    case '\n':
        line++;
        break;
    default:
        // multi-character tokens
        if (isNumerical(peek()))
        {
            scanNumber();
        }
        else if (isValidVariable(peek()))
        {
            scanIdentifier();
        }
    }
}

void Scanner::scanNumber()
{
    start = current;
    bool foundDecimalPoint = false;

    while (peek() != EOF_CHARACTER && isNumerical(peek()))
    {
        if (peek() == '.' && foundDecimalPoint)
        {
            throw ScannerException();
        }
        if (peek() == '.' && !foundDecimalPoint)
        {
            foundDecimalPoint = true;
        }
        advance();
    }

    int span = current - start;
    string str = trim(fileContents.substr(start, span));
    if (foundDecimalPoint)
    {
        if (str[0] != '.')
        {
            addToken(std::stod(str));
        }
        else if (str[str.length() - 1] == '.')
        {
            addToken(std::stod(str));
        }
        else
        {
            addToken(std::stod("0" + str));
        }
    }
    else
    {
        addToken(std::stoi(str));
    }
    prev();
}
void Scanner::scanString()
{
    start = current;
    while (peek() != EOF_CHARACTER && !(peek() == '\"' || peek() == '\''))
    {
        advance();
    }
    if (peek() == '\0')
    {
        throw ScannerException();
    }
    // +1 because start = 25, current = 26 - we would like to get char 25 (char 26 broke something)
    int span = current - start;
    string str = (fileContents.substr(start, span));
    addToken(str, false);
    prev();
}
void Scanner::scanIdentifier()
{
    start = current;
    while (peek() != EOF_CHARACTER && isValidVariable(peek()))
    {
        advance();
    }
    // +1 because start = 25, current = 26 - we would like to get char 25 (char 26 broke something)
    int span = current - start;
    string identifier = trim(fileContents.substr(start, span));
    if (identifier == "True")
    {
        addToken(true);
    }
    else if (identifier == "False")
    {
        addToken(false);
    }
    else if (reverseLexemeLookUp->count(identifier) != 0)
    {
        TokenType tokenType = reverseLexemeLookUp->at(identifier);
        addToken(tokenType);
    }
    else
    {
        addToken(identifier, true);
    }
    prev();
}

// when would we ever need to put something into the value param - done?
// answered: value takes strings and number and boolean - the literal values of the program
// what is the exact meaning of lexeme? - lexeme is the fundamental building block of a grammar
// a literal is non-changing value and is directly can be boiled down to low-level without changing
void Scanner::addTokenHelper(Token t)
{
    this->tokens->push_back(t);
}
void Scanner::addToken(string str, bool isIdentifier)
{
    Token *t;
    // todo - determine if the str is a keyword or not
    if (isIdentifier)
    {
        t = new Token(TokenType::IDENTIFIER, str, line, nullptr);
    }
    else
    {
        t = new Token(TokenType::STRING, str, line, str);
    }
    addTokenHelper(*t);
}
void Scanner::addToken(TokenType tokenType)
{
    if (lexemeLookUp->count(tokenType) != 0)
    {
        string s = lexemeLookUp->at(tokenType);
        Token t(tokenType, s, line, nullptr);
        addTokenHelper(t);
    }
}
void Scanner::addToken(int i)
{
    Token t(TokenType::INT, std::to_string(i), line, i);
    addTokenHelper(t);
}
void Scanner::addToken(double d)
{
    Token t(TokenType::DOUBLE, std::to_string(d), line, d);
    addTokenHelper(t);
}
void Scanner::addToken(bool b)
{
    Token t(TokenType::BOOL, std::to_string(b), line, b);
    addTokenHelper(t);
}
void Scanner::scanTokens()
{
    while (peek() != EOF_CHARACTER)
    {
        // DONE - how to skip spaces?
        // just advance if see space
        start = current;
        this->consumeToken();
        advance();
    }
}
void Scanner::advance()
{
    this->current++;
}
void Scanner::prev()
{
    this->current--;
}
void Scanner::printTokens()
{
    string ret = tokensToString();
    std::cout << ret;
}

string Scanner::tokensToString()
{

    string ret = "";
    for (int i = 0; i < tokens->size(); i++)
    {
        ret += tokens->at(i).toString() + "\n";
    }
    return ret.substr(0, ret.length() - 1);
}