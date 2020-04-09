#include "Measure.hpp"

using namespace am;

Measure::Measure(std::string name, int bpm, int repetitions, TimeSignature *timeSignature):
    name(std::move(name)),
    bpm(bpm),
    repetitions(repetitions),
    timeSignature(timeSignature)
{

}

Measure::~Measure()
{
    delete timeSignature;
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

std::unique_ptr<TimeSignature> Measure::getTimeSignature()
{
    return std::unique_ptr<TimeSignature>(timeSignature);
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

void Measure::setTimeSignature(TimeSignature *timeSignature)
{
    this->timeSignature = timeSignature;
}