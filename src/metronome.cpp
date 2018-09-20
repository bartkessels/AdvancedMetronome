#include "metronome.h"

#include <QAudioDeviceInfo>

static const int MINUTE_IN_MS = 60 * 1000;

Metronome::Metronome(QObject *parent)
    : QObject(parent)
{
    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, &QTimer::timeout, this, &Metronome::performBeat);

    m_accent.setSource(QUrl("qrc:/accent"));
    m_tick.setSource(QUrl("qrc:/tick"));

    setBpm(218);
    setBeats(4);
}

void Metronome::setBpm(const int bpm) {
    m_bpm = qBound(10, bpm, 999);
    emit changed();
}

void Metronome::setBeats(const int beats) {
    m_beats = qBound(1, beats, 9);
    emit changed();
}

void Metronome::start() {
    m_currentBeat = 0;
    m_timer.start(0);
    emit changed();
}

void Metronome::stop() {
    m_timer.stop();
    emit changed();
}

void Metronome::toggle() {
    if (isActive()) {
        stop();
    } else {
        start();
    }
}

void Metronome::performBeat() {
    if (m_currentBeat++ >= m_beats) {
        m_currentBeat = 1;
    }

    (m_currentBeat == 1 ? &m_accent : &m_tick)->play();

    const int interval = MINUTE_IN_MS / m_bpm;
    if (m_timer.interval() != interval) {
        m_timer.setInterval(interval);
    }

    emit changed();
}

bool Metronome::tap() {
    if (m_tap.isValid()) {
        setBpm(MINUTE_IN_MS / m_tap.elapsed());
        m_tap.invalidate();

        return true;
    }

    m_tap.start();
    return false;
}
