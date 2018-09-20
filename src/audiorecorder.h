#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QAudioRecorder>
#include <QUrl>

class AudioRecorder : public QObject
{
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = nullptr);

signals:

public slots:
    void stop();

private:
    QAudioRecorder* recorder;
};

#endif // AUDIORECORDER_H
