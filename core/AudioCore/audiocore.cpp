#include "audiocore.h"
#include "fourier.h"

AudioCore::AudioCore()
{
    primaryAudioData = NULL;
    fourierAudioData = NULL;
    destinationFile.setFileName("./output_for_gnuplot.txt");
}

AudioCore::~AudioCore()
{
    delete audio;
    if (primaryAudioData) delete[] primaryAudioData;
    if (fourierAudioData) delete[] fourierAudioData;
}

void AudioCore::recordAudioSample(int t = 500, bool writeToFile = false)
{
    latestSampleDuration = t;
    writeSampleToFile    = writeToFile;

    sampleAudioBuffer.open(QBuffer::ReadWrite);
    QAudioFormat format;

    // Настраиваем желаемый формат, например:
    format.setSampleRate(AudioCore::SampleRate);
    format.setSampleSize(8 * AudioCore::SampleSize);
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // ВЫбрать устройство ввода 0:
    QAudioDeviceInfo info(QAudioDeviceInfo::availableDevices(QAudio::AudioInput).at(0));
    qDebug() << "Selected input device =" << info.deviceName();

    if (!info.isFormatSupported(format)) {
       qWarning() << "Default format not supported, trying to use the nearest.";
       format = info.nearestFormat(format);
    }

    audio = new QAudioInput(format);

    // Очень важно, иначе будут шумы и все картинки ужасно некрасивые.
    audio->setVolume(AudioCore::AudioLevel);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    QTimer::singleShot(t, this, SLOT(stopRecording()));
    audio->start(&sampleAudioBuffer);
}

void AudioCore::stopRecording()
{
    audio->stop();

    QByteArray data = sampleAudioBuffer.data();
    if (primaryAudioData) delete[] primaryAudioData;

    if (writeSampleToFile) {
        destinationFile.open( QIODevice::WriteOnly | QIODevice::Truncate );
    }

    latestAllocatedSize = data.size() / AudioCore::SampleSize;
    primaryAudioData = new double[latestAllocatedSize];

    qDebug() << "Recorded this number of values:" << latestAllocatedSize;

    for (int i = 0; i < data.size(); i ++) {
        int res = 0;

        if (i % AudioCore::SampleSize == 0) {
            if (i + 4 < data.size()) {
                for (int j = 0; j < AudioCore::SampleSize; j ++) {
                    res += data[i  + j] << (j * 8);
                }
            }
            primaryAudioData[i / AudioCore::SampleSize] = (double) res;
            if (writeSampleToFile) {
                QString number = QString::number(res);
                destinationFile.write(number.toStdString().c_str());
                destinationFile.write("\n");
            }
        }
    }

    if (writeSampleToFile) {
         destinationFile.close();
    }

    emit endedRecordingAndProcessing();
}

double * AudioCore::getAudioSampleFourier()
{
    int nn = AudioCore::FFTN * 2;
    if (primaryAudioData && latestAllocatedSize > nn) {
        if (fourierAudioData) delete[] fourierAudioData;
        fourierAudioData = new double[nn];


        qDebug() << "Fourier length is: " << nn;

        memcpy(fourierAudioData, primaryAudioData, nn * sizeof(double));
        qDebug() << "Processing FFT";
        four1(fourierAudioData, nn / 2, 1);

        qDebug() << "Returning FFT result";
        return fourierAudioData;
    }

    return NULL;
}

void AudioCore::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::StoppedState:
            if (audio->error() != QAudio::NoError) {
                qDebug() << "Error occured in handleStateChanged";
            } else {
                qDebug() << "Ended handleStateChanged";
            }
            break;

        case QAudio::ActiveState:
                qDebug() << "Started handleStateChanged";
            break;

        default:
                qDebug() << "Other ocured in handleStateChanged";
            break;
    }
}
