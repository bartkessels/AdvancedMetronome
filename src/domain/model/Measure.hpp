#pragma once

#include <string>
#include "TimeSignature.hpp"

namespace am
{
    class Measure
    {
    public:
        Measure(std::string name, int bpm, int repetitions, TimeSignature *timeSignature);
        ~Measure();

        // Getters
        std::string getName();
        int getBpm();
        int getRepetitions();
        std::unique_ptr<TimeSignature> getTimeSignature();

        // Setters
        void setName(std::string name);
        void setBpm(int bpm);
        void setRepetitions(int repetitions);
        void setTimeSignature(TimeSignature *timeSignature);

    private:
        std::string name;
        int bpm{};
        int repetitions{};
        TimeSignature *timeSignature;
    };
}