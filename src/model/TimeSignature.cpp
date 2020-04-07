#include "model/TimeSignature.hpp"

using namespace am;

TimeSignature::TimeSignature(float numerator, float denominator):
        numerator(numerator),
        denominator(denominator)
{

}

int TimeSignature::getSignature()
{
    return (numerator / denominator) * denominator;
}

void TimeSignature::setDenominator(int denominator)
{
    this->denominator = denominator;
}

void TimeSignature::setNumerator(int numerator)
{
    this->numerator = numerator;
}