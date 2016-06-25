#include "audiocore.h"

AudioCore::AudioCore()
{
    destinationFile.setFileName("./test.raw");
}

AudioCore::~AudioCore()
{
    delete audio;
}

void AudioCore::RecordAudioToFile()
{
    destinationFile.open( QIODevice::WriteOnly | QIODevice::Truncate );

    QAudioFormat format;
    // Set up the desired format, for example:
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

//print out the input device setup parameters
     QAudioDeviceInfo info(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(0));     //select output device 0
     qDebug() << "Selected input device =" << info.deviceName();


    if (!info.isFormatSupported(format)) {
       qWarning() << "Default format not supported, trying to use the nearest.";
       format = info.nearestFormat(format);
    }

    audio = new QAudioInput(format);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    QTimer::singleShot(3000, this, SLOT(stopRecording()));
    audio->start(&destinationFile);
}

void AudioCore::stopRecording()
{
    audio->stop();
    destinationFile.close();
}

void AudioCore::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::StoppedState:
            if (audio->error() != QAudio::NoError) {
                // Error handling
            } else {
                qDebug() << "Stopp recording";
            }
            break;

        case QAudio::ActiveState:
            // Started recording - read from IO device
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}
