#ifndef TESTSCENE_H
#define TESTSCENE_H
#include "ctScene.h"
#include "ctTimer.h"
//#include <QMediaPlayer>
#include <QVector>
#include <QPoint>

class ctPlane;
class ctButton;
class ctClickablePlane;
class Block;
class hBricks;
class hCircles;

class testScene : public ctScene
{
public:
    enum GameStates
    {
        GS_GAME,
        GS_CREDITS,
        GS_MAINMENU
    };
private:
    float m_frame;
    int m_lastFPS;
    int frameCounter;
    int msecsCounter;
    ctPlane * m_back;
    ctPlane * m_winSprite;
    ctTimer * m_timer;
    QString m_isClicked;
    hCircles* t_circles;
    //------------------------------------
    bool m_isMusicPlay;
    //------------------------------------
    int m_gameState;
    //--------------------------------
    ctButton* m_resetButton;
    ctButton* m_undoButton;
    ctButton* m_menuButton;
    ctButton* m_newGameButton;
    ctButton* m_creditsButton;
    ctPlane * m_credits_txt;
    hBricks * m_bricks;

    ctButton* m_soundButton;
    //--------------------------------

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

    virtual void Freeze();
    virtual void Unfreeze();

    virtual void Update();

    void TimerTest();

    void ResetBlocks(bool t_fast = false);
    void ResetButtonOnPres();

    int GetGameState();
    void SetGameState(int);
    void ShowCredits();
    void ShowGame();
    void ShowMainMenu();

    bool IsMusicPlay();
    void PauseMusic();
    void PlayMusic();
    void SwitchMusic();
};

#endif // TESTSCENE_H
