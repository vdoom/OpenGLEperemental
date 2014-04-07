#ifndef BLOCK_H
#define BLOCK_H
#include "ctClickablePlane.h"
class Block : public ctClickablePlane
{
public:
    enum block_color
    {
        BC_BLUE,
        BC_RED
    };
private:
    int m_blockSize, m_blockColor;
protected:
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
public:
    explicit Block(ctShaderManager *);
    Block(ctShaderManager *, ctScene *);
    Block(ctShaderManager *, ctScene *, QOpenGLContext *);
    Block(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    Block(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type, int t_blockSize, int t_blockColor);
    virtual ~Block();

    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual ctEntity* Clone();
    //-----------------------------------------
    int GetBlockSize() const;
    int GetBlockColor() const;
};

#endif // BLOCK_H
