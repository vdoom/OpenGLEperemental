#ifndef CTLOGER_H
#define CTLOGER_H

#include <QDebug>
#include <QString>

class ctLoger
{
private:
    ctLoger();
    ~ctLoger();
public:
    void SendLog(QString t_str);

    static ctLoger* GetLoger()
    {
        static ctLoger* s_instance = 0;
        if(!s_instance)
        {
            s_instance = new ctLoger();
        }
        return s_instance;
    }
};

#endif // CTLOGER_H
