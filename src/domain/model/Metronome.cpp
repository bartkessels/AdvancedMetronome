#include "Metronome.hpp"

using namespace am;

Metronome::~Metronome()
{
    static_cast<void>(measures.empty());
}

void Metronome::addMeasure(Measure *measure)
{
    measures.push_back(measure);
}

void Metronome::removeMeasure(Measure *measure)
{
    static_cast<void>(std::remove(measures.begin(), measures.end(), measure));
    measures.pop_back();
}

void Metronome::swapMeasure(Measure *measureA, Measure *measureB)
{
    const auto measureAIndex = std::find(measures.begin(), measures.end(), measureA);
    const auto measureBIndex = std::find(measures.begin(), measures.end(), measureB);

    std::iter_swap(measureAIndex, measureBIndex);
}

std::vector<Measure*> Metronome::getMeasures()
{
    return measures;
}
