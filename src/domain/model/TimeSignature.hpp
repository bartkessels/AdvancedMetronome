#pragma once

namespace am
{
    class TimeSignature
    {
    public:
        TimeSignature(float numerator, float denominator);
        ~TimeSignature() = default;

        // Getters
        int getSignature();

        // Setters
        void setNumerator(float numerator);
        void setDenominator(float denominator);

    private:
        float denominator;
        float numerator;
    };
}