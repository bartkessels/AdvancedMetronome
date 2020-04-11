#include "Metronome.hpp"

using namespace am;

void Metronome::addMeasure(std::shared_ptr<Measure> measure)
{
    measures.push_back(measure);
}

void Metronome::removeMeasure(std::shared_ptr<Measure> measure)
{
    static_cast<void>(std::remove(measures.begin(), measures.end(), measure));
    measures.pop_back();
}

void Metronome::swapMeasure(std::shared_ptr<Measure> measureA, std::shared_ptr<Measure> measureB)
{
    const auto measureAIndex = std::find(measures.begin(), measures.end(), measureA);
    const auto measureBIndex = std::find(measures.begin(), measures.end(), measureB);

    std::iter_swap(measureAIndex, measureBIndex);
}

std::vector<std::shared_ptr<Measure>> Metronome::getMeasures()
{
    return measures;
}
