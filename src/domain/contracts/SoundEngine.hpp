#pragma once

namespace am
{
    struct SoundEngine
    {
    public:
        virtual ~SoundEngine() = default;

        virtual void playAccent() = 0;
        virtual void playTick() = 0;
    };
}