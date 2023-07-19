#include "mocks/ScannerMock.cpp"
#include "Scanner.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <filesystem>

using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
namespace fs = std::filesystem;

bool fileExists(const std::string &filePath)
{
	return fs::exists(filePath) && fs::is_regular_file(filePath);
}

void testPythonFile(string filePath, string expectedFilePath)
{
	if (!fileExists(filePath) || !fileExists(expectedFilePath))
	{
		FAIL() << "File not found " << filePath;
		return;
	}
	std::ifstream file;
	file.open(filePath);

	std::ifstream expectedFile;
	expectedFile.open(expectedFilePath);
	std::stringstream buffer;
	buffer << expectedFile.rdbuf();
	NiceMock<ScannerMock> scanner(&file);
	scanner.scanTokens();
	string str = scanner.tokensToString();
	EXPECT_EQ(str, buffer.str());
}

TEST(Scanner, IdentifiesVariableAssignment)
{
	testPythonFile("./testcases/input/basic.py", "./testcases/output/basic.txt");
}
TEST(Scanner, IdentifiesFunctions)
{

	testPythonFile("./testcases/input/function.py", "./testcases/output/function.txt");
}
TEST(Scanner, IdentifiesDoubles)
{

	testPythonFile("./testcases/input/decimal.py", "./testcases/output/decimal.txt");
}
TEST(Scanner, IdentifiesTabs)
{
	testPythonFile("./testcases/input/tab.py", "./testcases/output/tab.txt");
}
TEST(Scanner, IdentifiesComents)
{
	testPythonFile("./testcases/input/comment.py", "./testcases/output/comment.txt");
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}