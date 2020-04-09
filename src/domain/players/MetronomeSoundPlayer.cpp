#include "MetronomeSoundPlayer.hpp"

using namespace am;

MetronomeSoundPlayer::MetronomeSoundPlayer(SoundEngine *soundEngine):
    soundEngine(soundEngine)
{

}

void MetronomeSoundPlayer::play(Metronome metronome)
{
    // On first tick of measure
    soundEngine->playAccent();

    // On regular tick of measure
    soundEngine->playTick();
}