#include "SignalWait.h"
#include "QTime"

bool SignalWait::Wait(const int msTimeout)
{
    QTime Timer(0,0,0,msTimeout);

    Timer.start();

    while(m_SignalSpy.isEmpty() == true && Timer.elapsed() < msTimeout)
    {
        QCoreApplication::processEvents();
    }

    return (!m_SignalSpy.isEmpty());
}
