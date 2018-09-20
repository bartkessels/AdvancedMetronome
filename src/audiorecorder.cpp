#include "audiorecorder.h"

#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include <QMultimedia>
#include <QAudioBuffer>
#include <QAudio>

AudioRecorder::AudioRecorder(QObject *parent) : QObject(parent)
{
    QAudioBuffer* buffer = new QAudioBuffer();

    Q_UNUSED(buffer);
}

void AudioRecorder::stop()
{
    recorder->stop();
}
