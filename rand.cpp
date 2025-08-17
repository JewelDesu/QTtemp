#include "rand.h"
#include <QMutex>


RandThread::RandThread(QObject* parent, bool b):
    QThread(parent), Stop(b)
{

}

void RandThread::run()
{
    for(int i = 0; i<= 60; i++)
    {
        QMutex mutex;

        mutex.lock();
            if(this->Stop) break;
        mutex.unlock();
    }
}
