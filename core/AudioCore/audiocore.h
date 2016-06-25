#ifndef AUDIOCORE_H
#define AUDIOCORE_H

#include <QFile>
#include <QDebug>
#include <QAudioInput>
#include <QTimer>
#include <QObject>
#include <QIODevice>
#include <QAudioOutput>

class AudioCore : public QObject
{
public:
    AudioCore();

    void RecordAudioToFile();
    void StopRecording();
    void handleStateChanged(QAudio::State);
private:
    QFile destinationFile;   // Class member
    QAudioInput* audio;
};

#endif // AUDIOCORE_H
