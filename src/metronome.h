#pragma once

#include <QObject>

#include <QElapsedTimer>
#include <QSoundEffect>
#include <QTimer>

class Metronome : public QObject
{
    Q_OBJECT
public:
    explicit Metronome(QObject *parent = nullptr);

    int bpm() const { return m_bpm; }
    void setBpm(const int bpm);

    int beats() const { return m_beats; }
    void setBeats(const int beats);

    int currentBeat() const { return m_currentBeat; }
    bool isActive() const { return m_timer.isActive(); }

    bool tap();

private:
    QTimer m_timer;
    QElapsedTimer m_tap;

    int m_bpm;
    int m_currentBeat;
    int m_beats;

    QSoundEffect m_accent;
    QSoundEffect m_tick;


signals:
    void changed();

public slots:
    void start();
    void stop();
    void toggle();

private slots:
    void performBeat();
};

