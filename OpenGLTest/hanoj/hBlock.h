#ifndef BLOCK_H
#define BLOCK_H
#include "ctClickablePlane.h"
#include "ctMover.h"

class Block : public ctClickablePlane
{
public:
    enum block_color
    {
        BC_BLUE = 0,
        BC_CYAN = 1,
        BC_RED = 2,
        BC_GREEN = 3,
        BC_ORANGE = 4,
        BC_PURPPLE = 5,
        BC_GRAY = 6,
        BC_YELLOW = 7
    };
private:
    int m_blockSize, m_blockColor;
    ctMover* m_mover;
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

    void AutoMove(QVector3D t_start, QVector3D t_end);

//    bool operator <(const Block &a, const Block &b)
//    {
//        if(a.GetTransform()->)
//    }

    static QString GetColor(int t_colorCode)
    {
        switch(t_colorCode)
        {
        case BC_BLUE:
            return "blue";
        case BC_CYAN:
            return "cyan";
        case BC_GRAY:
            return "gray";
        case BC_GREEN:
            return "green";
        case BC_ORANGE:
            return "orange";
        case BC_PURPPLE:
            return "purpple";
        case BC_RED:
            return "red";
        case BC_YELLOW:
            return "yellow";
        }
    }
	
    int G_indexqqq;
};

#endif // BLOCK_H
