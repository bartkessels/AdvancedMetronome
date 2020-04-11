#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "domain/model/Measure.hpp"

namespace am
{
    class Metronome
    {
    public:
        Metronome() = default;
        ~Metronome() = default;

        void addMeasure(std::shared_ptr<Measure> measure);
        void removeMeasure(std::shared_ptr<Measure> measure);
        void swapMeasure(std::shared_ptr<Measure> measureA, std::shared_ptr<Measure> measureB);

        std::vector<std::shared_ptr<Measure>> getMeasures();

    private:
        std::vector<std::shared_ptr<Measure>> measures;
    };
}