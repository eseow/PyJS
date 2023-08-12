// File: MathFunctionsTest.cpp

#include "gtest/gtest.h"
int add(int a, int b)
{
    return a + b;
}
TEST(AddTest, PositiveNumbers)
{
    // Arrange
    int a = 5;
    int b = 10;

    // Act
    int result = add(a, b);

    // Assert
    EXPECT_EQ(result, 15);
}

TEST(AddTest, NegativeNumbers)
{
    // Arrange
    int a = -5;
    int b = -10;

    // Act
    int result = add(a, b);

    // Assert
    EXPECT_EQ(result, -15);
}

TEST(AddTest, Zero)
{
    // Arrange
    int a = 0;
    int b = 0;

    // Act
    int result = add(a, b);

    // Assert
    EXPECT_EQ(result, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
