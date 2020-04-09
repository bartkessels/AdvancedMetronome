#pragma once

#include <QtMultimedia/QSoundEffect>

#include "domain/contracts/SoundEngine.hpp"

namespace am
{
    class QtSoundEngine: public SoundEngine
    {
    public:
        QtSoundEngine();
        ~QtSoundEngine() override = default;

        void playAccent() override;
        void playTick() override;

    private:
        QSoundEffect accent;
        QSoundEffect tick;
    };
}