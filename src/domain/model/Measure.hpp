#pragma once

#include <memory>
#include <string>
#include "TimeSignature.hpp"

namespace am
{
    class Measure
    {
    public:
        Measure(std::string name, int bpm, int repetitions, std::unique_ptr<TimeSignature> timeSignature);
        ~Measure() = default;

        // Getters
        std::string getName();
        int getBpm();
        int getRepetitions();
        TimeSignature *getTimeSignature();

        // Setters
        void setName(std::string name);
        void setBpm(int bpm);
        void setRepetitions(int repetitions);

    private:
        std::string name;
        int bpm{};
        int repetitions{};
        std::unique_ptr<TimeSignature> timeSignature;
    };
}