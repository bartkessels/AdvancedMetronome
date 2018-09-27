#pragma once

#include <QObject>
#include <QSoundEffect>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>

#include "imetronome.h"
#include "imeasure.h"
#include "measure.h"

class Metronome : public QObject, public IMetronome
{
    Q_OBJECT
    Q_INTERFACES(IMetronome)

public:
    explicit Metronome(QObject *parent = nullptr);
    virtual ~Metronome();

    // Measure
    void addMeasure();
    void addMeasure(IMeasure *measure);
    void addMeasure(QJsonObject jsonMeasure);
    void deleteMeasures();

    // Metronome
    void start(bool preMetronomeTicks = false);
    void stop();
    void setupPreMetronome(int bpm, int ticks);

    // JSON
    QJsonArray getMeasuresAsJsonArray();
    void loadMeasuresFromJson(QJsonArray jsonMeasures);

private:
    void nextMeasure();
    void playPreMetronomeTicks();

signals:
    void notifyTick(int totalRepetitions, int currentRepetition);
    void notifyChangeMeasure(IMeasure *measure);
    void notifyAddMeasure(IMeasure *measure);
    void notifyStop();
    void notifyMeasureMoveUp(IMeasure *measure);
    void notifyMeasureMoveDown(IMeasure *measure);

public slots:
    void on_measureMoveUp(IMeasure *measure);
    void on_measureMoveDown(IMeasure *measure);
    void on_measureDelete(IMeasure *measure);

private slots:
    void on_timerTick();

private:

    // Default values
    const int DEFAULT_CURRENT_MEASURE_COUNT = 0;
    const int DEFAULT_CURRENT_BEAT = 1; // Must be one because the time-signature is 1-indexed
    const int PRE_METRONOME_TIME_SIGNATURE_INDEX = 0;

    // Keep track of measures
    int currentRepetition = DEFAULT_CURRENT_MEASURE_COUNT;
    int currentBeat = DEFAULT_CURRENT_BEAT;
    IMeasure *currentMeasure;

    QList<IMeasure*> measures;

    // Pre metronome
    IMeasure *preMetronome;

    QTimer timer;
    QSoundEffect metronomeAccent;
    QSoundEffect metronomeTick;
};

