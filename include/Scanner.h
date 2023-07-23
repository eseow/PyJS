#ifndef SCANNER_H
#define SCANNER_H
#include <fstream>
#include <vector>
#include "Token.h"
#include <map>
#include <iostream>
using std::map;
using std::string;
using std::vector;

enum TokenTextType
{
    TEXT_IDENTIFIER,
    TEXT_COMMENT,
    TEXT_STRING
};

class Scanner
{
public:
    virtual ~Scanner(){};
    void initFileContents(std::ifstream *file);
    void scanString();
    void scanNumber();
    void scanIdentifier();
    bool matchNext(char matching);
    // look into - how to cut down on addToken amount
    void addTokenHelper(Token t);
    void addToken(string str, TokenTextType tokenTextType);
    void addToken(TokenType tokenType);
    void addToken(int i);
    void addToken(double d);
    void addToken(bool b);
    virtual void scanTokens();
    void consumeToken();
    void advance();
    void prev();
    char peek();
    char peekNext();
    void scanComment();
    Scanner(std::ifstream *file);
    Scanner(){};
    char *charArray;
    void printTokens();
    vector<Token> *getTokens();
    virtual string tokensToString();

private:
    vector<Token> *tokens;
    int column;
    int current;
    int start;
    int line;
    int lengthOfFile;
    string fileContents;
    std::map<TokenType, std::string> *lexemeLookUp;
    map<string, TokenType> *reverseLexemeLookUp;
};
#endif
