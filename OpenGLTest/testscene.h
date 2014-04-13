#ifndef TESTSCENE_H
#define TESTSCENE_H
#include "ctScene.h"
#include "ctTimer.h"
//#include <QMediaPlayer>
#include <QVector>

class ctPlane;
class ctClickablePlane;
class Block;

class testScene : public ctScene
{
private:
    float m_frame;
    int m_lastFPS;
    int frameCounter;
    int msecsCounter;
    ctPlane * m_plane;
    ctPlane * m_plane2;
    ctPlane * m_back;
    ctTimer * m_timer;
    QString m_isClicked;
    Block * m_block;
    ctClickablePlane * m_selected;
    QVector<Block*> m_blocks;
    //QMediaPlayer * m_sound;
    bool dragMode;

    QVector<ctClickablePlane*> m_coliderObjects;

    QVector<QVector<Block*>*> m_blockSlots;
    QVector<Block*> m_movingStash;

    void GenerateBlocks();
    void AddCollider(ctClickablePlane* );
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
    void AligneBlocks();

    Block* ManageRectClick(QVector<Block*>& t_blocks);

    ctClickablePlane* ManageCollide();
};

#endif // TESTSCENE_H
