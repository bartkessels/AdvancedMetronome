#pragma once

#include <QObject>
#include <QSoundEffect>
#include <QTimer>

#include <QDebug>

#include "measure.h"

class Metronome : public QObject
{
    Q_OBJECT

#define DEFAULT_CURRENT_MEASURE_COUNT 0
#define DEFAULT_CURRENT_BEAT 1

public:
    explicit Metronome(QObject *parent = nullptr);

    void setMeasure(Measure *measure);
    void start();
    void stop();

private:
    Measure *measure;

    int currentMeasureCount = DEFAULT_CURRENT_MEASURE_COUNT;
    int currentBeat = DEFAULT_CURRENT_BEAT;

    QTimer timer;

    QSoundEffect metronomeAccent;
    QSoundEffect metronomeTick;


signals:
    void measureEnded();

private slots:
    void tick();
};

