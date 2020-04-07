#include <catch2/catch.hpp>

#include "model/TimeSignature.hpp"

using namespace am;

/**
 * Test most common time signature
 *
 */
TEST_CASE("Calculating 4/4 time signature", "[TimeSignature]")
{
    // Arrange
    const int denominator = 4;
    const int numerator = 4;
    const int expectedResult = 4;

    auto signature = TimeSignature(numerator, denominator);

    // Act
    int result = signature.getSignature();

    // Assert
    CHECK(expectedResult == result);
}

/**
 * Test less common time signature
 *
 */
TEST_CASE("Calculate 15/1 time signature", "[TimeSignature]")
{
    // Arrange
    const int denominator = 1;
    const int numerator = 15;
    const int expectedResult = 15;

    auto signature = TimeSignature(numerator, denominator);

    // Act
    int result = signature.getSignature();

    // Assert
    CHECK(expectedResult == result);
}

/**
 * Test less common time signature
 *
 */
TEST_CASE("Calculate 32/8 time signature", "[TimeSignature]")
{
    // Arrange
    const int denominator = 8;
    const int numerator = 32;
    const int expectedResult = 32;

    auto signature = TimeSignature(numerator, denominator);

    // Act
    int result = signature.getSignature();

    // Assert
    CHECK(expectedResult == result);
}

/**
 * Test edge case for dividing
 *
 */
TEST_CASE("Calculate 15/16 time signature", "[TimeSignature]")
{
    // Arrange
    const int denominator = 16;
    const int numerator = 15;
    const int expectedResult = 15;

    auto signature = TimeSignature(numerator, denominator);

    // Act
    int result = signature.getSignature();

    // Assert
    CHECK(expectedResult == result);
}
