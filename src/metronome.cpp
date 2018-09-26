#include "metronome.h"

static const int MINUTE_IN_MS = 60 * 1000;

Metronome::Metronome(QObject *parent):
    QObject(parent)
{
    timer.setTimerType(Qt::PreciseTimer);
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timerTick()));

    metronomeAccent.setSource(QUrl("qrc:/sounds/accent"));
    metronomeTick.setSource(QUrl("qrc:/sounds/tick"));

    // Setup pre-metronome
    preMetronome = new Measure();
    preMetronome->setTimeSignatureIndex(PRE_METRONOME_TIME_SIGNATURE_INDEX, PRE_METRONOME_TIME_SIGNATURE_INDEX);
    preMetronome->setTitle(tr("Pre-metronome"));
}

// =============================================================================
// Measure

/**
 * @brief Metronome::addMeasure
 * @param measure the measure to add to the list
 *
 * Add the given measure to the list and connect all
 * the required signals
 *
 */
void Metronome::addMeasure(IMeasure *measure)
{
    measures.append(measure);

    connect(dynamic_cast<QObject*>(measure), SIGNAL(notifyMoveUp(IMeasure*)), this, SLOT(on_measureMoveUp(IMeasure*)));
    connect(dynamic_cast<QObject*>(measure), SIGNAL(notifyMoveDown(IMeasure*)), this, SLOT(on_measureMoveDown(IMeasure*)));
    connect(dynamic_cast<QObject*>(measure), SIGNAL(notifyDelete(IMeasure*)), this, SLOT(on_measureDelete(IMeasure*)));

    emit notifyAddMeasure(measure);
}

/**
 * @brief Metronome::addMeasure
 *
 * Create empty measure and add it to the measures list
 *
 */
void Metronome::addMeasure()
{
    IMeasure *measure = new Measure();
    addMeasure(measure);
}

/**
 * @brief Metronome::addMeasure
 * @param jsonMeasure JSON representation of a measure
 *
 * Load a measure object from a json object and add
 * it to the list
 *
 */
void Metronome::addMeasure(QJsonObject jsonMeasure)
{
    IMeasure *measure = new Measure(jsonMeasure);
    addMeasure(measure);
}

/**
 * @brief Metronome::deleteMeasures
 *
 * Delete all measures from the list
 *
 */
void Metronome::deleteMeasures()
{
    measures.clear();
}

// =============================================================================
// Metronome

/**
 * @brief Metronome::start
 *
 * Start the timer; the actual metronome
 * handling is done on each timer::timeout
 *
 */
void Metronome::start(bool preMetronomeTicks)
{
    if (preMetronomeTicks) {
        currentMeasure = preMetronome;
    } else {
        currentMeasure = measures.first();
    }

    timer.start();
    emit notifyChangeMeasure(currentMeasure);
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
    currentMeasure = NULL;

    emit notifyStop();
}

/**
 * @brief Metronome::setupPreMetronome
 * @param bpm beats per minute the pre-metronome should tick
 * @param ticks number of ticks for the pre-metronome
 *
 * Set bpm and number of ticks that should occur before
 * starting the metronome
 *
 */
void Metronome::setupPreMetronome(int bpm, int ticks)
{
    preMetronome->setBpm(bpm);
    preMetronome->setRepetitions(ticks);
}

// =============================================================================
// JSON

/**
 * @brief Metronome::loadFromJson
 * @param jsonObject jsonArray containing all the measures
 *
 * Add all measures from the given json array
 *
 */
void Metronome::loadMeasuresFromJson(QJsonArray jsonMeasures)
{
    for (int index = 0; index < jsonMeasures.count(); index++) {
        QJsonObject jsonMeasure = jsonMeasures.at(index).toObject();
        addMeasure(jsonMeasure);
    }
}

/**
 * @brief Metronome::getJsonObject
 * @return json representation of the metronome
 *
 * Get a json object with all the measures
 *
 */
QJsonArray Metronome::getMeasuresAsJson()
{
    QJsonArray jsonMeasures;

    for (int index = 0; index < measures.size(); index++) {
        IMeasure *measure = measures.at(index);
        jsonMeasures.append(measure->getJsonObject());
    }

    return jsonMeasures;
}

// =============================================================================
// Private

/**
 * @brief Metronome::nextMeasure
 *
 * Set the currentMeasure variable to the next IMeasure object
 * in the list by incrementing the index of the currentMeasure
 * object; if the currentMeasure is the last measure in the list
 * the currentMeasure is set to NULL and the metronome will stop
 *
 */
void Metronome::nextMeasure()
{
    if (currentMeasure == NULL) {
        return;
    }

    int totalMeasures = measures.count();
    int currentMeasureIndex = measures.indexOf(currentMeasure);
    int nextMeasureIndex = currentMeasureIndex + 1;

    if (totalMeasures > 0 && nextMeasureIndex < totalMeasures) {
        currentMeasure = measures.at(nextMeasureIndex);
        emit notifyChangeMeasure(currentMeasure);
    } else {
        stop();
    }
}

// =============================================================================
// Slots

/**
 * @brief Metronome::on_measureMoveUp
 * @param measure measure that's being moved one place up
 *
 * Swap the given measure with the measure above if the given
 * measure isn't already on the top
 *
 */
void Metronome::on_measureMoveUp(IMeasure *measure)
{
    int measureIndex = measures.indexOf(measure);
    int measureIndexBelow = measureIndex - 1;

    if (measureIndexBelow >= 0 && measureIndex < measures.size()) {
        measures.swap(measureIndex, measureIndexBelow);

        emit notifyMeasureMoveDown(measure);
    }
}

/**
 * @brief Metronome::on_measureMoveDown
 * @param measure measure that's being moved one place down
 *
 * Swap the given measure with the measure below if the given
 * measure isn't already at the bottom
 *
 */
void Metronome::on_measureMoveDown(IMeasure *measure)
{
    int measureIndex = measures.indexOf(measure);
    int measureIndexAbove = measureIndex + 1;

    if (measureIndex >= 0 && measureIndexAbove < measures.size()) {
        measures.swap(measureIndex, measureIndexAbove);

        emit notifyMeasureMoveUp(measure);
    }
}

/**
 * @brief Metronome::on_measureDelete
 * @param measure the measure that's being deleted
 *
 * Remove the given measure from the measures list
 *
 */
void Metronome::on_measureDelete(IMeasure *measure)
{
    if (measures.contains(measure)) {
        measures.removeOne(measure);
    }
}

/**
 * @brief Metronome::on_timerTick
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
 * When emitting the notifyTick subtract 1 from the totalRepetitions
 * so it ends with 0 instead of 1
 *
 */
void Metronome::on_timerTick()
{
    if (currentMeasure == NULL) {
        return;
    }

    const int timeSignature = currentMeasure->getTimeSignature();
    const int repetitions = currentMeasure->getRepetitions();
    const int bpm = currentMeasure->getBpm();
    const int interval = MINUTE_IN_MS / bpm;

    (currentBeat == DEFAULT_CURRENT_BEAT ? &metronomeAccent : &metronomeTick)->play();
    emit notifyTick(repetitions, currentRepetition);

    if (currentBeat++ >= timeSignature) {
        currentBeat = DEFAULT_CURRENT_BEAT;
        currentRepetition++;
    }

    if (timer.interval() != interval) {
        timer.setInterval(interval);
    }

    if (currentRepetition >= repetitions) {
        currentRepetition = DEFAULT_CURRENT_MEASURE_COUNT;
        nextMeasure();
    }
}
