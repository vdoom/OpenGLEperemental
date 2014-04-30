#ifndef HBRICKS_H
#define HBRICKS_H

#include "ctObject.h"
#include "hanoj/hBlock.h"

class hBricks : public ctObject
{
private:
    QVector <Block*> blocks;
public:
    hBricks();
    explicit hBricks(ctShaderManager *);
    hBricks(ctShaderManager *, ctScene *);
    hBricks(ctShaderManager *, ctScene *, QGLContext *);
    virtual ~hBricks();

    virtual void Update();
    virtual void Draw();//=0;
    virtual void Init();//=0;
};

#endif // HBRICKS_H
