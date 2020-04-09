#pragma once

#include "domain/model/Metronome.hpp"

namespace am
{
    struct MetronomePlayer
    {
    public:
        virtual ~MetronomePlayer() = default;

        virtual void play(Metronome metronome) = 0;
    };
}