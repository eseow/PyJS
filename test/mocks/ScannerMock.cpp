#include "Scanner.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>

class ScannerMock : public Scanner
{
public:
    ScannerMock() {}
    ScannerMock(std::ifstream *file)
    {
        real = new Scanner(file);
        ON_CALL(*this, scanTokens()).WillByDefault([this]()
                                                   { std::cout << "Running to scanTokens"; real->scanTokens(); });
        ON_CALL(*this, tokensToString()).WillByDefault([this]()
                                                       { std::cout << "Running to tokensToString"; return real->tokensToString(); });
    };
    MOCK_METHOD(void, scanTokens, (), (override));
    MOCK_METHOD(string, tokensToString, (), (override));

private:
    Scanner *real = nullptr;
};