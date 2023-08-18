#include "Parser.h"
#include "Scanner.h"
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
        scanner->scanTokens();
        parser = new Parser(scanner->getTokens());
        ON_CALL(*this, parse()).WillByDefault([this]()
                                              { parser->parse(); });
        ON_CALL(*this, getExprsString()).WillByDefault([this]()
                                                       { return parser->getExprsString(); });
    };
    MOCK_METHOD(void, parse, (), (override));
    MOCK_METHOD(std::string, getExprsString, (), (override));

private:
    Scanner *scanner = nullptr;
    Parser *parser = nullptr;
};