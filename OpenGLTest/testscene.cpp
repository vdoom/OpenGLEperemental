#include "testscene.h"
//#include "ctPlane.h"
#include "ctClickablePlane.h"
#include "ctShaderManager.h"
#include "ctWindow.h"
#include "ctTime.h"
#include "shaders.h"
#include "ctInput.h"
#include "ctInputEvent.h"
#include "hanoj/hBlock.h"
#include <QDesktopWidget>
#include "ctRand.h"
#include "ctButton.h"
#include "ctMover.h"
#include "hanoj/hCircles.h"
#include "hanoj/hBricks.h"

#define Input GetWindow()->GetInput()->GetInputHelper()

testScene::testScene()
{
    SetIsFreezable(true);
}

testScene::testScene(ctShaderManager * t_shaderManager) : ctScene(t_shaderManager)
{
    SetIsFreezable(true);
}

testScene::testScene(ctShaderManager * t_shaderManager, QOpenGLContext * t_OpenGLContext) : ctScene(t_shaderManager, t_OpenGLContext)
{
    SetIsFreezable(true);
}

testScene::~testScene()
{

}

void testScene::Init()
{
//    QDesktopWidget *mydesk;
//    mydesk
    ctScene::Init();
    m_lastFPS = 0;
    //dragMode = false;
    SetDragMode(false);
    //m_selected = 0;
    m_isClicked = "not";

    qDebug()<<"init testScene";

    //-------------------------------------------------
    //((QObject*)this);
    GetWindow()->GetMediaPlayer()->setMedia(QUrl("assets:/muse.mp3"));//(QUrl::fromLocalFile("c:\\muse.mp3"));//(QUrl("assets:/muse.mp3"));
    //GetWindow()->GetMediaPlayer()->setMedia(QUrl::fromLocalFile("c:\\muse.mp3"));
    GetWindow()->GetMediaPlayer()->setVolume(50);
    GetWindow()->GetMediaPlayer()->play();
    m_isMusicPlay = true;
    //-------------------------------------------------

    //GetWindow()->GetOpenGLContext()->makeCurrent();
    SetDefault(GetShaderManager(), 0, GetWindow()->GetOpenGLContext());//GetOpenGLContext());
    //m_plane2 = new ctPlane(GetShaderManager(), 0, GetOpenGLContext(), QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    //m_plane = new ctClickablePlane(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,50,0), QVector3D(-50,-50,0), ctPlane::Textured);
    m_back = new ctPlane(GetShaderManager(), this,GetOpenGLContext(), QVector3D(512,384,-20), QVector3D(-512, -384, -20), ctPlane::Colored);
    m_timer = new ctTimer();
    m_back->SetColor(QVector3D(0.61f, 1.0f, 0.85f));
    m_bricks = new hBricks(GetShaderManager(), this, GetOpenGLContext(), 0);
    m_resetButton = new ctButton(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512,384,1), QVector3D(-512, -384, 1), ctPlane::Textured, GetWindow()->GetInput());
    m_undoButton = new ctButton(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512,384,1), QVector3D(-512, -384, 1), ctPlane::Textured, GetWindow()->GetInput());
    m_menuButton = new ctButton(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512, 384, 1), QVector3D(-512, -384, 1), ctPlane::Textured, GetWindow()->GetInput());
    m_newGameButton = new ctButton(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512,384,1), QVector3D(-512, -384, 1), ctPlane::Textured, GetWindow()->GetInput());
    m_creditsButton = new ctButton(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512, 384, 1), QVector3D(-512, -384,1), ctPlane::Textured, GetWindow()->GetInput());
    m_credits_txt = new ctPlane(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512, 384, 1), QVector3D(-512,-384,1), ctPlane::Textured);
    m_winSprite = new ctPlane(GetShaderManager(), this, GetOpenGLContext(), QVector3D(10,10,1), QVector3D(-10,-10,1), ctPlane::Textured);
    m_soundButton = new ctButton(GetShaderManager(), this, GetOpenGLContext(), QVector3D(512, 384, 1), QVector3D(-512,-384,1), ctPlane::Textured, GetWindow()->GetInput());
    m_soundButton->SetTextureGrid(2,1);
    m_soundButton->SetFrame(1);
    //m_resetButton->SetColor(QVector3D(0.0f, 1.0f, 0));
    //m_block = new Block(GetShaderManager(), this, GetOpenGLContext(), QVector3D(50,10,1), QVector3D(-50,-10,1), ctPlane::Textured, 7,Block::BC_BLUE);
   // ctMover * t_mover = new ctMover();
    //m_resetButton->AddComponnent(t_mover);
   // t_mover->SetUp(QVector3D(400,400, 1), QVector3D(-400, -400, 1),10000, true, m_resetButton->GetTransform());
    //t_mover->Start();
    m_timer->SetTimer(5000, true);
    m_timer->GetDelegat()->AppendConnect(this, &testScene::TimerTest);
    t_circles = new hCircles(GetShaderManager(), this, GetOpenGLContext());
    t_circles->GetTransform()->Move(QVector3D(0,0,0));
    t_circles->Init();
    m_bricks->Init();
    m_bricks->SetProjectionMatrixtt(*GetProjectionMatrix());
    m_bricks->SetWinPlane(m_winSprite);
    //m_plane2->InitShader("texturedPlaneShader");
    //m_plane->InitShader("texturedPlaneShader");
    //m_plane2->SetTexture("D:\\OpenGLEperemental\\OpenGLTest\\txture.png");//(":/texture/txture.png");//("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    //m_plane->SetTexture(":/texture/txture.png");//("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    //m_back->SetTexture(":/texture/back.jpg");
    m_resetButton->SetTexture(":/texture/reset.png",true);
    m_undoButton->SetTexture(":/texture/undo.png", true);
    m_menuButton->SetTexture(":/texture/GUI/menu.png", true);
    m_newGameButton->SetTexture(":/texture/GUI/new_game.png", true);
    m_creditsButton->SetTexture(":/texture/GUI/credits.png", true);
    m_credits_txt->SetTexture(":/texture/GUI/credits_txt.png", true);
    m_soundButton->SetTexture(":/texture/GUI/sound_button_atlas.png", true);
    m_resetButton->GetOnPush()->AppendConnect(this, &testScene::ResetButtonOnPres);
	m_undoButton->GetOnPush()->AppendConnect(m_bricks, &hBricks::UndoStep);
    m_menuButton->GetOnPush()->AppendConnect(this, &testScene::ShowMainMenu);
    m_newGameButton->GetOnPush()->AppendConnect(this, &testScene::ShowGame);
    m_creditsButton->GetOnPush()->AppendConnect(this, &testScene::ShowCredits);
    m_soundButton->GetOnPush()->AppendConnect(this, &testScene::SwitchMusic);
    m_winSprite->SetTexture(":/texture/GUI/win.png",true);
    //m_block->SetTexture(":/texture/blue_7.png");

    //m_block->Init();
    //m_plane->Init();
    m_back->Init();
    m_resetButton->Init();
	m_undoButton->Init();
    m_menuButton->Init();
    m_newGameButton->Init();
    m_creditsButton->Init();
    m_winSprite->Init();
    m_credits_txt->Init();
    m_winSprite->Hide();
    m_soundButton->Init();

    m_resetButton->GetTransform()->Scale(QVector3D(0.6f, 0.6f, 1.0f));
    m_resetButton->GetTransform()->Move(QVector3D(-400,-320,0));
    m_undoButton->GetTransform()->Scale(QVector3D(0.6f, 0.65f, 1.0f));
    m_undoButton->GetTransform()->Move(QVector3D(-200,-320,0));
    m_menuButton->GetTransform()->Scale(QVector3D(0.6f, 0.6f, 1.0f));
    m_menuButton->GetTransform()->Move(QVector3D(400, -320, 0));
    m_newGameButton->GetTransform()->Scale(QVector3D(1,1,1));
    m_newGameButton->GetTransform()->Move(QVector3D(0,-100,1));
    m_creditsButton->GetTransform()->Scale(QVector3D(1,1,1));
    m_creditsButton->GetTransform()->Move(QVector3D(0,100,1));
    m_credits_txt->GetTransform()->Scale(QVector3D(1.5f,1.5f,1));
    m_credits_txt->GetTransform()->Move(QVector3D(0,0,1));
    m_soundButton->GetTransform()->Scale(QVector3D(0.6f, 0.6f, 1.0f));
    m_soundButton->GetTransform()->Move(QVector3D(200, -320, 0));
    //rootTransform->Hide();
    glClearColor(1.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
    if(! ctTime::GetTime())//Time)
    {qDebug()<<"Fuck\n";}
    m_frame = 0;

    SetGameState(GS_MAINMENU);

    AddObject(t_circles);
    AddObject(m_back);
    AddObject(m_resetButton);
	AddObject(m_undoButton);
    AddObject(m_menuButton);
    AddObject(m_soundButton);
    AddObject(m_newGameButton);
    AddObject(m_creditsButton);
    AddObject(m_bricks);
    AddObject(m_winSprite);
    AddObject(m_credits_txt);
}

void testScene::TimerTest()
{
    qDebug()<<"TimerTested";
}

void testScene::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    ctScene::SetDefault(t_shaderManager, t_scene, t_OpenGLContext);

    GetShaderManager()->AddFragmentShader(fragmentShaderSource, "fragmentShaderSource");
    GetShaderManager()->AddVertexShader(vertexModelShaderSource, "vertexModelShaderSource");
    GetShaderManager()->AddFragmentShader(texturedFragmentShaderSource, "texturedFragmentShaderSource");
    GetShaderManager()->AddVertexShader(texturedVertexShaderSource, "texturedVertexShaderSource");
    GetShaderManager()->AddVertexShader(texturedModelVertexShaderSource, "texturedModelVertexShaderSource");
    GetShaderManager()->AddFragmentShader(lineFragmentShaderSource, "lineFragmentShaderSource");
    GetShaderManager()->AddVertexShader(lineVertexShaderSource, "lineVertexShaderSource");
    GetShaderManager()->SetUpShaderProgram("vertexModelShaderSource", "fragmentShaderSource", "coloredShader");
    GetShaderManager()->SetUpShaderProgram("lineVertexShaderSource", "lineFragmentShaderSource", "lineShader");
    GetShaderManager()->SetUpShaderProgram("texturedModelVertexShaderSource", "texturedFragmentShaderSource", "texturedPlaneShader");
}

void testScene::BeginDraw()
{
    ctScene::BeginDraw();
    //-----------------TEMPORARY-SOLUTION-------------------------
    glViewport(0, 0, GetWindow()->GetWidth(), GetWindow()->GetHeight());
    //------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1);
    ++frameCounter;
    if(msecsCounter<1000)msecsCounter += ctTime::GetTime()->GetDeltaTime();
    else {m_lastFPS=frameCounter; msecsCounter = 0;frameCounter=0;}

    //DrawText(QPointF(30,30), QString::number(m_lastFPS));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void testScene::Draw()
{
    ctScene::Draw();

    QVector<ctObject*>::Iterator itr;
    for( itr = m_objects->begin(); itr != m_objects->end(); ++itr)
    {
        (*itr)->SetProjectionMatrix(matrix);
    }
}

void testScene::EndDraw()
{
    ctScene::EndDraw();
    m_frame+=1.0f;
    if(m_frame > 360) m_frame = m_frame - 360;


    GetWindow()->DrawText(QPointF(30,30), QString::number(m_lastFPS));
    GetWindow()->DrawText(QPointF(30, 60), m_isClicked);
	
    GetWindow()->DrawText(QPointF(30, 90), QString("X: ") + QString::number(GetWindow()->GetInput()->GetInputHelper().GetMousePos3D().x()));
    GetWindow()->DrawText(QPointF(30, 120), QString("Y: ") + QString::number(GetWindow()->GetInput()->GetInputHelper().GetMousePos3D().y()));
	
    //glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
}
void testScene::Update()
{
    ctScene::Update();

    ctTime::GetTime()->Update();
}

void testScene::ResetBlocks(bool t_fast)
{
    qDebug()<<"Reset";
    m_winSprite->Hide();
    if(m_bricks)
    {
        m_bricks->ResetBlocks(t_fast);
    }
}

void testScene::ResetButtonOnPres()
{
    ResetBlocks(false);
}

int testScene::GetGameState()
{ return m_gameState;}

void testScene::SetGameState(int t_gstate)
{
    switch(t_gstate)
    {
        case GS_CREDITS:
        {
            ShowCredits();
            break;
        }
        case GS_GAME:
        {
            ShowGame();
            break;
        }
        case GS_MAINMENU:
        {
            ShowMainMenu();
            break;
        }
    }
}

void testScene::ShowCredits()
{
    m_credits_txt->Show();
    m_resetButton->Hide();
    m_undoButton->Hide();
    m_menuButton->Show();
    m_newGameButton->Hide();
    m_creditsButton->Hide();
    m_bricks->Hide();
}

void testScene::ShowGame()
{
    m_credits_txt->Hide();
    m_resetButton->Show();
    m_undoButton->Show();
    m_menuButton->Show();
    m_newGameButton->Hide();
    m_creditsButton->Hide();
    m_bricks->Show();
    ResetBlocks(true);
}

void testScene::ShowMainMenu()
{
    m_credits_txt->Hide();
    m_resetButton->Hide();
    m_undoButton->Hide();
    m_menuButton->Hide();
    m_newGameButton->Show();
    m_creditsButton->Show();
    m_bricks->Hide();
}

bool testScene::IsMusicPlay()
{
    return m_isMusicPlay;
}

void testScene::PauseMusic()
{
    GetWindow()->GetMediaPlayer()->pause();
    m_soundButton->SetFrame(0);
}

void testScene::PlayMusic()
{
    GetWindow()->GetMediaPlayer()->play();
    m_soundButton->SetFrame(1);
}

void testScene::SwitchMusic()
{
    qDebug()<<"Switch";
    if(IsMusicPlay())
    {
        m_isMusicPlay = false;
        PauseMusic();
    }
    else
    {
        m_isMusicPlay = true;
        PlayMusic();
    }
}

void testScene::Freeze()
{
    PauseMusic();
}

void testScene::Unfreeze()
{
    if(IsMusicPlay())
    {
        PlayMusic();
    }
}
