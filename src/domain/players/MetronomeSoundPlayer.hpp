#pragma once

#include <memory>

#include "domain/contracts/MetronomePlayer.hpp"
#include "domain/contracts/SoundEngine.hpp"

namespace am
{
    class MetronomeSoundPlayer: public MetronomePlayer
    {
    public:
        explicit MetronomeSoundPlayer(SoundEngine *soundEngine);
        ~MetronomeSoundPlayer() override = default;

        void play(Metronome metronome) override;

    private:
        SoundEngine *soundEngine;
        int currentMeasureIndex = 0;

        const int MINUTE_IN_MS = 60 * 1000;
    };
}