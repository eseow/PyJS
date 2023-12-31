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
    void addToken(string str, bool isIdentifier);
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
    Scanner(std::ifstream *file);
    Scanner(){};
    char *charArray;
    void printTokens();
    virtual string tokensToString();

private:
    vector<Token> *tokens;
    int current;
    int start;
    int line;
    int lengthOfFile;
    string fileContents;
    std::map<TokenType, std::string> *lexemeLookUp;
    map<string, TokenType> *reverseLexemeLookUp;
};
#endif
