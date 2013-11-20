#ifndef CTLOGER_H
#define CTLOGER_H

#include <QDebug>
#include <QString>

class ctLoger
{
public:
    ctLoger();
    ~ctLoger();
    void SendLog(QString t_str);
};

#endif // CTLOGER_H
