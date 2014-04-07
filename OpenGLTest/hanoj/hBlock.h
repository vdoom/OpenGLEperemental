#ifndef BLOCK_H
#define BLOCK_H
#include "ctClickablePlane.h"
class Block : public ctClickablePlane
{
private:
protected:
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
public:
    explicit Block(ctShaderManager *);
    Block(ctShaderManager *, ctScene *);
    Block(ctShaderManager *, ctScene *, QOpenGLContext *);
    Block(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);

    virtual ~Block();

    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual ctEntity* Clone();
};

#endif // BLOCK_H
