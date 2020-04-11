#include <catch2/catch.hpp>

#include "domain/model/TimeSignature.hpp"

using namespace am;

TEST_CASE("Calculate time signatures", "[TimeSignature]")
{
    SECTION("4/4 - Most common time signature")
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

    SECTION("15/1 - Less common time signature")
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

    SECTION("32/8 - Less common time signature")
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

    SECTION("15/16 - Dividing edge case")
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
}