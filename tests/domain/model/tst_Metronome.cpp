#include <catch2/catch.hpp>
#include <memory>

#include "domain/model/Measure.hpp"
#include "domain/model/Metronome.hpp"

using namespace am;

TEST_CASE("Managing measures", "[Metronome]")
{
    const int bpm = 120;
    const int repetitions = 1;

    const int numerator = 4;
    const int denominator = 4;

    auto timeSignatureA = std::make_unique<TimeSignature>(numerator, denominator);
    auto timeSignatureB = std::make_unique<TimeSignature>(numerator, denominator);
    auto timeSignatureC = std::make_unique<TimeSignature>(numerator, denominator);
    auto timeSignatureD = std::make_unique<TimeSignature>(numerator, denominator);

    auto measureA = std::make_shared<Measure>("measureA", bpm, repetitions, std::move(timeSignatureA));
    auto measureB = std::make_shared<Measure>("measureB", bpm, repetitions, std::move(timeSignatureB));
    auto measureC = std::make_shared<Measure>("measureC", bpm, repetitions, std::move(timeSignatureC));
    auto measureD = std::make_shared<Measure>("measureD", bpm, repetitions, std::move(timeSignatureD));

    SECTION("Add a new measure to the end of the measures")
    {
        // Arrange
        auto metronome = Metronome();

        // Pre-assert
        CHECK(metronome.getMeasures().empty());

        // Act
        metronome.addMeasure(measureA);

        // Assert
        CHECK(!metronome.getMeasures().empty());
    }

    SECTION("Remove measure from beginning and move the other measures to the front")
    {
        // Arrange
        auto metronome = Metronome();

        metronome.addMeasure(measureA);
        metronome.addMeasure(measureB);

        // Pre-assert
        CHECK(metronome.getMeasures().front() == measureA);
        CHECK(metronome.getMeasures().back() == measureB);

        // Act
        metronome.removeMeasure(measureA);

        // Assert
        CHECK(metronome.getMeasures().front() == measureB);
        CHECK(metronome.getMeasures().back() == measureB);
        CHECK(metronome.getMeasures().size() == 1);
    }

    SECTION("Remove the measure from the middle and moves the other measures to the empty spaces")
    {
        // Arrange
        auto metronome = Metronome();

        metronome.addMeasure(measureA);
        metronome.addMeasure(measureB);
        metronome.addMeasure(measureC);
        metronome.addMeasure(measureD);

        // Pre-assert
        CHECK(metronome.getMeasures().at(0) == measureA);
        CHECK(metronome.getMeasures().at(1) == measureB);
        CHECK(metronome.getMeasures().at(2) == measureC);
        CHECK(metronome.getMeasures().at(3) == measureD);

        // Act
        metronome.removeMeasure(measureB);

        // Assert
        CHECK(metronome.getMeasures().at(0) == measureA);
        CHECK(metronome.getMeasures().at(1) == measureC);
        CHECK(metronome.getMeasures().at(2) == measureD);
        CHECK(metronome.getMeasures().size() == 3);
    }

    SECTION("Replace measureA with measureB and measureB with measureA")
    {
        // Arrange
        auto metronome = Metronome();

        metronome.addMeasure(measureA);
        metronome.addMeasure(measureB);

        // Pre-assert
        CHECK(metronome.getMeasures().at(0) == measureA);
        CHECK(metronome.getMeasures().at(1) == measureB);

        // Act
        metronome.swapMeasure(measureA, measureB);

        // Assert
        CHECK(metronome.getMeasures().at(0) == measureB);
        CHECK(metronome.getMeasures().at(1) == measureA);
    }
}

