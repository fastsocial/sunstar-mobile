#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QAudioInput>
#include "audiocore.h"
#include "SignalWait.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    AudioCore * core = new AudioCore();
    core->recordAudioSample(500, true);
    SignalWait sw((QObject *)core, SIGNAL(endedRecordingAndProcessing()));
    if(sw.Wait(1000)) {

        QFile fourierOut;
        fourierOut.setFileName("fourier.txt");
        fourierOut.open( QIODevice::WriteOnly | QIODevice::Truncate );

        int len = AudioCore::FFTN * 2;
        double * fft = core->getAudioSampleFourier();
        for (int i = 0; i < len; i ++) {
            fourierOut.write(QString::number(fft[i]).toStdString().c_str());
            fourierOut.write("\n");
        }
        fourierOut.close();
    }

    qDebug() << "Program ended";
    delete core;
    return a.exec();
}
