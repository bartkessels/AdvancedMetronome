#include "QtSoundEngine.hpp"

using namespace am;

QtSoundEngine::QtSoundEngine()
{
    accent.setSource(QUrl("qrc:/sounds/accent"));
    tick.setSource(QUrl("qrc:/sounds/tick"));
}

void QtSoundEngine::playAccent()
{
    accent.play();
}

void QtSoundEngine::playTick()
{
    tick.play();
}