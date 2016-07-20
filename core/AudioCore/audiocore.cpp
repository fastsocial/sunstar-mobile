#include "audiocore.h"

AudioCore::AudioCore()
{
    destinationFile.setFileName("./output_for_gnuplot.txt");
}

AudioCore::~AudioCore()
{
    delete audio;
}

void AudioCore::RecordAudioToFile()
{
    destinationFile.open( QIODevice::WriteOnly | QIODevice::Truncate );
    audioBuffer.open(QBuffer::ReadWrite);
    QAudioFormat format;

    // Set up the desired format, for example:
    format.setSampleRate(441000);
    format.setChannelCount(1);
    format.setSampleSize(32);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(0));     //select output device 0
    qDebug() << "Selected input device =" << info.deviceName();


    if (!info.isFormatSupported(format)) {
       qWarning() << "Default format not supported, trying to use the nearest.";
       format = info.nearestFormat(format);
    }

    audio = new QAudioInput(format);

    // Очень важно, иначе будут шумы и все картинки ужасно некрасивые.
    audio->setVolume(0.1);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    QTimer::singleShot(10000, this, SLOT(stopRecording()));
    audio->start(&audioBuffer);
}

void AudioCore::stopRecording()
{
    audio->stop();
    qDebug() << QString::number(audioBuffer.data().size());
    QByteArray data = audioBuffer.data();
    for (int i = 0; i < data.size(); i ++) {
        int res = 0;

        if (i % 4 == 0) {
            if (i + 4 < data.size()) {
                for (int j = 0; j < 4; j ++) {
                    res += data[i  + j] << (j * 8);
                }
            }
            QString number = QString::number(res);
            destinationFile.write(number.toStdString().c_str());
            destinationFile.write("\n");
        }
    }
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
