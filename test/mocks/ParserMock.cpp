#include "Parser.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>

class ParserMock : public Parser 
{
public:
    ParserMock() {}
    ParserMock(std::ifstream *file)
    {

        scanner = new Scanner(file);
        
        ON_CALL(*this, scanTokens()).WillByDefault([this]()
                                                   { std::cout << "Running to scanTokens"; real->scanTokens(); });
        ON_CALL(*this, tokensToString()).WillByDefault([this]()
                                                       { std::cout << "Running to tokensToString"; return real->tokensToString(); });
    };
    MOCK_METHOD(void, scanTokens, (), (override));
    MOCK_METHOD(string, tokensToString, (), (override));

private:
    Scanner *scanner = nullptr;
    Parser *parser = nullptr;
};