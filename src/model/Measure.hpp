#pragma once

#include <string>
#include "model/TimeSignature.hpp"

namespace am
{
    class Measure
    {
    public:
        Measure() = default;
        ~Measure() = default;

        void start();
        void stop();

        // Getters
        std::string getName() { return name; }
        int getBpm() { return bpm; }
        int getRepetitions() { return repetitions; }
        bool getIsPlaying() { return isPlaying; }

        // Setters
        void setName(std::string name) { this->name = std::move(name); }
        void setBpm(int bpm) { this->bpm = bpm; }
        void setRepetitions(int repetitions) { this->repetitions = repetitions; }

    private:
        std::string name;
        int bpm;
        int repetitions;
        bool isPlaying = false;
    };
}