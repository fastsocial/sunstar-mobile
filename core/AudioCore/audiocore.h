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
        void RecordAudioToFile();

    public slots:

        void stopRecording();
        void handleStateChanged(QAudio::State);

    signals:

    private:
        QFile destinationFile;   // Class member
        QBuffer audioBuffer;
        QAudioInput* audio;
};

#endif // AUDIOCORE_H
