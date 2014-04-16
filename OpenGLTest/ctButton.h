#ifndef CTBUTTON_H
#define CTBUTTON_H
#include "ctClickablePlane.h"

class ctButton : public ctClickablePlane
{
public:
    explicit ctButton(ctShaderManager *);
    ctButton(ctShaderManager *, ctScene *);
    ctButton(ctShaderManager *, ctScene *, QOpenGLContext *);
    ctButton(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
};

#endif // CTBUTTON_H
