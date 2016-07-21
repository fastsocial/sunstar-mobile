#ifndef AUDIOCORE_H
#define AUDIOCORE_H

#include <QFile>
#include <QDebug>
#include <QAudioInput>
#include <QTimer>
#include <QObject>
#include <QIODevice>
#include <QBuffer>
#include <QAudioOutput>

class AudioCore : public QObject
{
    Q_OBJECT

    public:
        AudioCore();
        ~AudioCore();
        void recordAudioSample(int, bool);
        double *getAudioSampleFourier();

        static const double AudioLevel = 0.1;
        static const int    SampleSize = 4;
        static const int    SampleRate = 44100;
        static const int    FFTN       = 2048;

    public slots:
        void stopRecording();
        void handleStateChanged(QAudio::State);

    signals:
        void endedRecordingAndProcessing();

    private:
        QFile destinationFile;
        QBuffer sampleAudioBuffer;
        QAudioInput* audio;
        int latestSampleDuration;
        bool writeSampleToFile;
        double *primaryAudioData;
        double *fourierAudioData;
        int latestAllocatedSize;
};

#endif // AUDIOCORE_H
