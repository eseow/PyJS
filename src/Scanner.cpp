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
    this->column = 0;
    this->current = 0;
    this->start = 0;
    this->line = 0;
    initFileContents(file);
    this->tokens = new std::vector<Token>();
    this->lexemeLookUp = Token::tokenLexemeMap;
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
    case '#':
        scanComment();
        break;
    case '\t':
        addToken(TokenType::TAB);
        break;
    case '\"':
        scanString();
        break;
    case '\'':
        scanString();
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
            addToken(TokenType::MODULO);
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
        addToken(TokenType::NEWLINE);
        line++;
        column = 0;
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
            throw ScannerException(line, start, "Number has multiple decimal points");
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

    bool isOneTick = false;
    if (peek() == '\'')
    {
        isOneTick = true;
    }
    advance();
    start = current;
    while (peek() != EOF_CHARACTER && !(peek() == '\"' || peek() == '\''))
    {
        advance();
    }
    if (peek() == '\0' || (peek() == '\"' && isOneTick) || (peek() == '\'' && !isOneTick))
    {
        throw ScannerException(line, column, "String is missing other quotes");
    }
    // +1 because start = 25, current = 26 - we would like to get char 25 (char 26 broke something)
    int span = current - start;
    string str = (fileContents.substr(start, span));
    addToken(str, TokenTextType::TEXT_STRING);
}
void Scanner::scanComment()
{
    advance();
    start = current;
    while (peek() != EOF_CHARACTER && !(peek() == '\n'))
    {
        advance();
    }
    int span = current - start;
    string str = (fileContents.substr(start, span));
    addToken(str, TokenTextType::TEXT_COMMENT);
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
        addToken(identifier, TokenTextType::TEXT_IDENTIFIER);
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
void Scanner::addToken(string str, TokenTextType tokenTextType)
{
    Token *t;
    switch (tokenTextType)
    {
    case TokenTextType::TEXT_COMMENT:
        t = new Token(TokenType::HASH, str, line, column, str);
        break;
    case TokenTextType::TEXT_STRING:
        t = new Token(TokenType::STRING, str, line, column, str);
        break;
    case TokenTextType::TEXT_IDENTIFIER:
        t = new Token(TokenType::IDENTIFIER, str, line, column, str);
        break;
    default:
        break;
    }
    // todo - determine if the str is a keyword or not
    addTokenHelper(*t);
}
void Scanner::addToken(TokenType tokenType)
{
    if (lexemeLookUp->count(tokenType) != 0)
    {
        string s = lexemeLookUp->at(tokenType);
        Token t(tokenType, s, line, column, s);
        addTokenHelper(t);
    }
}
void Scanner::addToken(int i)
{
    Token t(TokenType::INT, std::to_string(i), line, column, i);
    addTokenHelper(t);
}
void Scanner::addToken(double d)
{
    Token t(TokenType::DOUBLE, std::to_string(d), line, column, d);
    addTokenHelper(t);
}
void Scanner::addToken(bool b)
{
    Token t(TokenType::BOOL, std::to_string(b), line, column, b);
    addTokenHelper(t);
}
void Scanner::scanTokens()
{
    while (peek() != EOF_CHARACTER)
    {
        // DONE - how to skip spaces?
        // just advance if see space
        start = current;
        try
        {
            this->consumeToken();
        }
        catch (ScannerException &error)
        {
            std::cout << "\n"
                      << error.what();
            return;
        }
        advance();
    }
}
void Scanner::advance()
{
    this->current++;
    this->column++;
}
void Scanner::prev()
{
    this->current--;
}

string Scanner::tokensToString()
{

    string ret = "";
    for (int i = 0; i < (int)tokens->size(); i++)
    {
        ret += tokens->at(i).toString() + "\n";
    }
    return ret.substr(0, ret.length() - 1);
}

vector<Token> *Scanner::getTokens()
{
    return tokens;
}