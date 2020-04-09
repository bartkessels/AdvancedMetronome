#include <catch2/catch.hpp>

#include "domain/model/Metronome.hpp"

using namespace am;

const int bpm = 120;
const int repetitions = 1;

const int numerator = 4;
const int denominator = 4;

TEST_CASE("addMeasure adds a new measure to the end of the measures", "[Metronome]")
{
    // Arrange
    auto metronome = Metronome();
    auto timeSignature = TimeSignature(numerator, denominator);
    auto measureA = new Measure("measureA", bpm, repetitions, &timeSignature);

    // Pre-assert
    CHECK(metronome.getMeasures().empty());

    // Act
    metronome.addMeasure(measureA);

    // Assert
    CHECK(!metronome.getMeasures().empty());
}

TEST_CASE("removeMeasure removes the measure from beginning and moves the other measures to the front", "[Metronome]")
{
    // Arrange
    auto metronome = Metronome();
    auto timeSignature = TimeSignature(numerator, denominator);
    auto measureA = new Measure("measureA", bpm, repetitions, &timeSignature);
    auto measureB = new Measure("measureB", bpm, repetitions, &timeSignature);

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
}

TEST_CASE("removeMeasure removes the measure from the middle and moves the other measures to the empty spaces", "[Metronome]")
{
    // Arrange
    auto metronome = Metronome();
    auto timeSignature = TimeSignature(numerator, denominator);
    auto measureA = new Measure("measureA", bpm, repetitions, &timeSignature);
    auto measureB = new Measure("measureB", bpm, repetitions, &timeSignature);
    auto measureC = new Measure("measureC", bpm, repetitions, &timeSignature);
    auto measureD = new Measure("measureD", bpm, repetitions, &timeSignature);

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

TEST_CASE("swapMeasure replaces measureA with measureB and measureB with measureA", "[Metronome]")
{
    // Arrange
    auto metronome = Metronome();
    auto timeSignature = TimeSignature(numerator, denominator);
    auto measureA = new Measure("measureA", bpm, repetitions, &timeSignature);
    auto measureB = new Measure("measureB", bpm, repetitions, &timeSignature);

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
