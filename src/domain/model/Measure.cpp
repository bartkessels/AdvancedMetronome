#include "Measure.hpp"

#include <utility>

using namespace am;

Measure::Measure(std::string name, int bpm, int repetitions, std::unique_ptr<TimeSignature> timeSignature):
    name(std::move(name)),
    bpm(bpm),
    repetitions(repetitions),
    timeSignature(std::move(timeSignature))
{

}

std::string Measure::getName()
{
    return name;
}

int Measure::getBpm()
{
    return bpm;
}

int Measure::getRepetitions()
{
    return repetitions;
}

TimeSignature *Measure::getTimeSignature()
{
    return timeSignature.get();
}

void Measure::setName(std::string name)
{
    this->name = std::move(name);
}

void Measure::setBpm(int bpm)
{
    this->bpm = bpm;
}

void Measure::setRepetitions(int repetitions)
{
    this->repetitions = repetitions;
}
