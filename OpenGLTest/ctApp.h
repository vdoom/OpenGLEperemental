#ifndef CTAPP_H
#define CTAPP_H

#include "ctWindow.h"

class ctApp
{
private:
    ctWindow * m_mainGameWindow;
    //Q_OBJECT
public:
    ctApp();
    virtual ~ctApp();
};

#endif // CTAPP_H
