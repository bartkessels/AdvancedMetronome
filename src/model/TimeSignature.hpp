#pragma once

#include <cmath>

namespace am
{
    class TimeSignature
    {
    public:
        TimeSignature() = default;
        TimeSignature(float numerator, float denominator);
        ~TimeSignature() = default;

        // Getters
        int getSignature();

        // Setters
        void setNumerator(int numerator);
        void setDenominator(int denominator);

    private:
        float denominator;
        float numerator;
    };
}