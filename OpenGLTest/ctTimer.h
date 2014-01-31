#ifndef CTTIMER_H
#define CTTIMER_H

#include "ctEntity.h"
#include "ctDelegat.h"

class ctTimer : public ctEntity
{
private:
    ctDelegat * m_delegat;
public:
    ctTimer();
};

#endif // CTTIMER_H
