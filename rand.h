#ifndef RAND_H
#define RAND_H

#include <QObject>
#include <QThread>
#include <windows.h>


class RandThread : public QThread
{
    Q_OBJECT
public:
    RandThread();
    explicit RandThread(QObject* parent = 0, bool b = false);
    void run();

    bool Stop;

    signals:
    void value(int);
    public slots:
};

#endif // RAND_H
