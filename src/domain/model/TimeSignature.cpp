#include "TimeSignature.hpp"

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

void TimeSignature::setDenominator(float denominator)
{
    this->denominator = denominator;
}

void TimeSignature::setNumerator(float numerator)
{
    this->numerator = numerator;
}