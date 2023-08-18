#include "mocks/ScannerMock.cpp"
#include "mocks/ParserMock.cpp"
#include "Scanner.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <filesystem>

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
namespace fs = std::filesystem;

const std::string SCANNER_TEST_SUITE = "./testcases/Scanner";
const std::string PARSER_TEST_SUITE = "./testcases/Parser";

std::map<std::string, std::string> *getTestCaseFiles(std::string TEST_SUITE, std::string fileName)
{
    std::map<std::string, std::string> *map = new std::map<std::string, std::string>;
    map->insert({"input", TEST_SUITE + "/input/" + fileName + ".py"});
    map->insert({"output", TEST_SUITE + "/output/" + fileName + ".txt"});
    return map;
}

bool fileExists(const std::string &filePath)
{

    return fs::exists(filePath) && fs::is_regular_file(filePath);
}

void testcase(std::string TEST_SUITE, std::string fileName)
{
    std::map<std::string, std::string> *testcaseFiles = getTestCaseFiles(TEST_SUITE, fileName);
    std::string input = testcaseFiles->at("input");
    std::string output = testcaseFiles->at("output");

    if (!fileExists(input) || !fileExists(output))
    {
        FAIL() << "File not found "
               << "input:" << input << " output:" << output;
        return;
    }
    std::ifstream file;
    file.open(input);

    std::ifstream expectedFile(output);
    std::stringstream expectedOutput;
    expectedOutput << expectedFile.rdbuf();
    string actualOutput;

    if (TEST_SUITE == SCANNER_TEST_SUITE)
    {
        NiceMock<ScannerMock> scanner(&file);
        scanner.scanTokens();
        actualOutput = scanner.tokensToString();
    }
    else if (TEST_SUITE == PARSER_TEST_SUITE)
    {
        NiceMock<ParserMock> parser(&file);
        parser.parse();
        actualOutput = parser.getExprsString();
    }
    try
    {
        ASSERT_EQ(actualOutput, expectedOutput.str());
    }
    catch (...)
    {
        Scanner *scanner = new Scanner(&file);
        scanner->scanTokens();
        std::cout << "Scanner:" << scanner->tokensToString() << std::endl;
        Parser *parser = new Parser(scanner->getTokens());
        parser->parse();
        std::cout << "Parser:" << parser->getExprsString() << std::endl;
    }
}

TEST(Scanner, IdentifiesVariableAssignment)
{
    testcase(SCANNER_TEST_SUITE, "basic");
}

TEST(Scanner, IdentifiesFunctions)
{
    testcase(SCANNER_TEST_SUITE, "function");
}
TEST(Scanner, IdentifiesDoubles)
{
    testcase(SCANNER_TEST_SUITE, "decimal");
}
TEST(Scanner, IdentifiesTabs)
{
    testcase(SCANNER_TEST_SUITE, "tab");
}
TEST(Scanner, IdentifiesComments)
{
    testcase(SCANNER_TEST_SUITE, "comment");
}
TEST(Scanner, IdentifiesStrings)
{
    testcase(SCANNER_TEST_SUITE, "string");
}
TEST(Scanner, DoesFizzbuzz)
{
    testcase(SCANNER_TEST_SUITE, "fizzbuzz");
}
TEST(Scanner, DetectsScannerException)
{
    testcase(SCANNER_TEST_SUITE, "scannerException");
}

TEST(Parser, ParsesInlineExpr)
{
    testcase(SCANNER_TEST_SUITE, "comparison");
    testcase(PARSER_TEST_SUITE, "comparison");
}

/*

intermediate representation to convert py -> inter -> js
AST for "for ... in ..." - "def ... (n?)"

*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}