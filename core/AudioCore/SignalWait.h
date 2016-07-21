#ifndef SIGNALWAIT_H
#define SIGNALWAIT_H

#endif // SIGNALWAIT_H

#include <QSignalSpy>

class SignalWait
{
    QSignalSpy m_SignalSpy;

public:

    SignalWait(QObject *object, const char *signal) : m_SignalSpy(object, signal) {}

    bool Wait(const int msTimeout);
};
