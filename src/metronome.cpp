#include "metronome.h"

static const int MINUTE_IN_MS = 60 * 1000;

Metronome::Metronome(QObject *parent)
    : QObject(parent)
{
    timer.setTimerType(Qt::PreciseTimer);
    connect(&timer, &QTimer::timeout, this, &Metronome::tick);

    metronomeAccent.setSource(QUrl("qrc:/sounds/accent"));
    metronomeTick.setSource(QUrl("qrc:/sounds/tick"));
}

/**
 * @brief Metronome::setMeasure
 * @param measure the new measure to be played
 *
 * Set a new measure that needs to be played
 *
 */
void Metronome::setMeasure(Measure *measure)
{
    this->measure = measure;
}

/**
 * @brief Metronome::tick
 *
 * Play a tick or accent sound based on the current beat index;
 * if the current beat index is the first beat of the measure
 * an accent is being played to notify the user that a new measure
 * has begon, given any other value a regular 'tick' is being played
 *
 * This method also keeps track of the allowed times this measure
 * needs to be played; if the total play times exceeds the allowed
 * play times notify the MainWindow that the measure is done
 *
 */
void Metronome::tick()
{
    if (measure == NULL) {
        return;
    }

    (currentBeat == DEFAULT_CURRENT_BEAT ? &metronomeAccent : &metronomeTick)->play();
    if (currentBeat++ >= measure->getTimeSignature()) {
        currentBeat = DEFAULT_CURRENT_BEAT;
        currentMeasureCount++;
    }

    const int interval = MINUTE_IN_MS / measure->getBeatsPerMinute();
    if (timer.interval() != interval) {
        timer.setInterval(interval);
    }

    if (currentMeasureCount >= measure->getNumberOfRepeats()) {
        currentMeasureCount = DEFAULT_CURRENT_MEASURE_COUNT;
        emit measureEnded();
    }
}

/**
 * @brief Metronome::start
 *
 * Start the timer; the actual metronome
 * handling is done on each timer::timeout
 *
 */
void Metronome::start()
{
    timer.start();
}

/**
 * @brief Metronome::stop
 *
 * Stop the timer and set all the
 * variables to their default values
 *
 */
void Metronome::stop()
{
    timer.stop();
    measure = nullptr;

    currentBeat = DEFAULT_CURRENT_BEAT;
    currentMeasureCount = DEFAULT_CURRENT_MEASURE_COUNT;
}
