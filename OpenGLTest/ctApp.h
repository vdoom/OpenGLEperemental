#ifndef CTAPP_H
#define CTAPP_H

//#include "ctWindow.h"
class ctWindow;
class ctScene;

class ctApp
{
private:
    ctWindow * m_mainGameWindow;
    ctScene * m_mainScene;
    //Q_OBJECT
public:
    ctApp();
    virtual ~ctApp();
    void Init();
    void Update();
    //TODO: need create Update method (perheps in parallel thread)
};

#endif // CTAPP_H
