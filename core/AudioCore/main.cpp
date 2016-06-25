#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QAudioInput>
#include "audiocore.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream out(stdout);


    AudioCore core;
    core.RecordAudioToFile();

    out << "hello beautiful world!" << endl << endl;

    return a.exec();
}
