#ifndef TESTSCENE_H
#define TESTSCENE_H
#include "ctScene.h"
#include "ctTimer.h"
//#include <QMediaPlayer>
#include <QVector>
#include <QPoint>

class ctPlane;
class ctClickablePlane;
class Block;
class hBricks;

class testScene : public ctScene
{
private:
    float m_frame;
    int m_lastFPS;
    int frameCounter;
    int msecsCounter;
    ctPlane * m_back;
    ctPlane * m_winSprite;
    ctTimer * m_timer;
    QString m_isClicked;
    hBricks * m_bricks;

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

    virtual void Update();

    void TimerTest();

    void ResetBlocks();
};

#endif // TESTSCENE_H
