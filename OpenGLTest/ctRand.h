#ifndef CTRAND_H
#define CTRAND_H

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>
#include "ctTime.h"

class ctRand
{
private:
    ctRand();
public:
    static int RandomReset()
    {
        srand(ctTime::GetTime()->GetMiliSecsSinceEpoch());
    }

    static int intRandom(int min, int max)
    {
        int tmp = (max+1) - min;
        return (rand()%tmp)+min;
    }
};

#endif // CTRAND_H
