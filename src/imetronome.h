#pragma once

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

#include "imeasure.h"

class IMetronome
{

public:
    virtual ~IMetronome() {}

    // Measure
    virtual void addMeasure(IMeasure *measure) = 0;
    virtual void addMeasure() = 0;
    virtual void addMeasure(QJsonObject jsonMeasure) = 0;
    virtual void deleteMeasures() = 0;

    // JSON
    virtual void loadMeasuresFromJson(QJsonArray jsonMeasures) = 0;
    virtual QJsonArray getMeasuresAsJson() = 0;

    // Metronome
    virtual void start(bool preMetronomeTicks = false) = 0;
    virtual void stop() = 0;
    virtual void setupPreMetronome(int bpm, int ticks) = 0;

private:
    virtual void nextMeasure() = 0;

public:

    // Signals
    virtual void notifyTick(int totalRepetitions, int currentRepetition) = 0;
    virtual void notifyChangeMeasure(IMeasure *measure) = 0;
    virtual void notifyAddMeasure(IMeasure *measure) = 0;
    virtual void notifyStop() = 0;
    virtual void notifyMeasureMoveUp(IMeasure *measure) = 0;
    virtual void notifyMeasureMoveDown(IMeasure *measure) = 0;

    // Slots
    virtual void on_measureMoveUp(IMeasure *measure) = 0;
    virtual void on_measureMoveDown(IMeasure *measure) = 0;
    virtual void on_timerTick() = 0;
};

Q_DECLARE_INTERFACE(IMetronome, "IMetronome")
