#pragma once

#include <vector>

#include "domain/model/Measure.hpp"

namespace am
{
    class Metronome
    {
    public:
        Metronome() = default;
        ~Metronome();

        void addMeasure(Measure *measure);
        void removeMeasure(Measure *measure);
        void swapMeasure(Measure *measureA, Measure *measureB);

        std::vector<Measure*> getMeasures();

    private:
        std::vector<Measure*> measures;
    };
}