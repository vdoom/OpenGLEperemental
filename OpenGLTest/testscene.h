#ifndef TESTSCENE_H
#define TESTSCENE_H
#include "ctScene.h"

class ctPlane;

class testScene : public ctScene
{
private:
    float m_frame;
    int m_lastFPS;
    int frameCounter;
    int msecsCounter;
    ctPlane * m_plane;
    ctPlane * m_plane2;
protected:
public:
    testScene();
    explicit testScene(ctShaderManager *);
    explicit testScene(ctShaderManager *, QOpenGLContext *);
    virtual ~testScene();

    virtual void Init();
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);

    virtual void BeginDraw();
    virtual void Draw();
    virtual void EndDraw();
};

#endif // TESTSCENE_H
