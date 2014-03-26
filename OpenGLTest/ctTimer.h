#ifndef CTTIMER_H
#define CTTIMER_H

#include "ctEntity.h"
//#include "ctDelegat.h"
#include "ctFastDelegat.h"

class ctTimer : public ctEntity
{
private:
    ctFastDelegat m_delegat;
    quint64 m_startTime;
    quint64 m_lifeTime;
    quint64 m_counter;
    bool m_isAlive;
    bool m_isCyclic;
public:
    ctTimer();
    ~ctTimer(){qDebug()<<"TimerDestroyed";}

    virtual void Update();
    virtual void Draw();
    virtual void Init();

    void SetTimer(quint64 t_lifetime, bool t_isCyclic = false);
    ctFastDelegat* GetDelegat();// const;
    void StopTimer();
};

#endif // CTTIMER_H
