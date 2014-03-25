#ifndef CTTIMER_H
#define CTTIMER_H

#include "ctEntity.h"
//#include "ctDelegat.h"
#include "ctFastDelegat.h"

class ctTimer : public ctEntity
{
private:
    //ctDelegat * m_delegat;
    ctFastDelegat* m_delegat;
    quint64 m_startTime;
    quint64 m_lifeTime;
public:
    ctTimer();

    virtual void Update();
    virtual void Draw();
    virtual void Init();

    void SetTimer(quint64 t_lifetime);
    ctFastDelegat* GetDelegat() const;
};

#endif // CTTIMER_H
