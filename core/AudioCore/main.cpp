#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QAudioInput>
#include "audiocore.h"
#include "SignalWait.h"
#include "mainwindow.h"
#include "plot.h"
#include <QVector>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AudioCore * core = new AudioCore();
    core->recordAudioSample(500, true);
    SignalWait sw((QObject *)core, SIGNAL(endedRecordingAndProcessing()));
    if(sw.Wait(1000)) {

        QFile fourierOut;
        fourierOut.setFileName("fourier.txt");
        fourierOut.open( QIODevice::WriteOnly | QIODevice::Truncate );
        int len = AudioCore::FFTN * 2;
        QVector<double> x(len), y(len);
        double * fft = core->getAudioSampleFourier();
        for (int i = 0; i < len; i ++) {
            x[i] = i;
            y[i] = fft[i];
            fourierOut.write(QString::number(fft[i]).toStdString().c_str());
            fourierOut.write("\n");
        }
        fourierOut.close();
        w.plot(x,y,0,len);
    }

    w.show();
    qDebug() << "Program ended";
    delete core;
    return a.exec();
}
