#ifndef CTBUTTON_H
#define CTBUTTON_H
#include "ctClickablePlane.h"
#include "ctFastDelegat.h"

class ctInput;

class ctButton : public ctClickablePlane
{
private:
    ctFastDelegat m_OnClick;
    ctFastDelegat m_OnPush;
    ctInput* m_input;
public:
    explicit ctButton(ctShaderManager *);
    ctButton(ctShaderManager *, ctScene *);
    ctButton(ctShaderManager *, ctScene *, QOpenGLContext *);
    ctButton(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type, ctInput*);

    ctFastDelegat* GetOnPush();

    virtual void Update();
};

#endif // CTBUTTON_H
