#include "testscene.h"
//#include "ctPlane.h"
#include "ctClickablePlane.h"
#include "ctShaderManager.h"
#include "ctWindow.h"
#include "ctTime.h"
#include "shaders.h"
#include "ctInput.h"
#include "ctInputEvent.h"
#include <QDesktopWidget>
testScene::testScene()
{
}

testScene::testScene(ctShaderManager * t_shaderManager) : ctScene(t_shaderManager)
{}

testScene::testScene(ctShaderManager * t_shaderManager, QOpenGLContext * t_OpenGLContext) : ctScene(t_shaderManager, t_OpenGLContext)
{}

testScene::~testScene()
{}

void testScene::Init()
{
//    QDesktopWidget *mydesk;
//    mydesk
    ctScene::Init();
    m_lastFPS = 0;
    m_isClicked = "not";

    qDebug()<<"init testScene";
    SetDefault(GetShaderManager(), 0, GetOpenGLContext());
    m_plane2 = new ctPlane(GetShaderManager(), 0, GetOpenGLContext(), QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    m_plane = new ctClickablePlane(GetShaderManager(), 0, GetOpenGLContext(), QVector3D(50,50,0), QVector3D(-50,-50,0), ctPlane::Textured);
    m_plane2->InitShader("texturedPlaneShader");
    //m_plane->InitShader("texturedPlaneShader");
    m_plane2->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    m_plane->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    //m_plane2->GetTransform()->RotateByX(0.2f);
    //m_plane2->GetTransform()->RotateByX(90.0f);
    //m_plane2->GetTransform()->RotateByZ(90.0f);
    //m_plane->GetTransform()->RotateByZ(0.2f);
    m_plane2->GetTransform()->Move(QVector3D(0,0,0));
    m_plane->GetTransform()->Move(QVector3D(0,0,0));
    m_plane2->GenerateCompleteBuffer();
   // m_plane->GenerateCompleteBuffer();
    m_plane->Init();
    //m_plane->GetTransform()->Scale(QVector3D(10.0f, 10.0f, 10.0f));
    //m_plane2->GetTransform()->SetParent(m_plane->GetTransform());
    //m_plane2->GetTransform()->Scale(QVector3D(10.0f, 10.0f, 10.0f));

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, GetWindow()->width(), GetWindow()->height());
    if(!ctTime::GetTime())
    {qDebug()<<"Fuck\n";}
    m_frame = 0;

    AddObject(m_plane);
    //AddObject(m_plane2);
}

void testScene::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    ctScene::SetDefault(t_shaderManager, t_scene, t_OpenGLContext);

    GetShaderManager()->AddFragmentShader(fragmentShaderSource, "fragmentShaderSource");
    GetShaderManager()->AddVertexShader(vertexShaderSource, "vertexShaderSource");
    GetShaderManager()->AddFragmentShader(texturedFragmentShaderSource, "texturedFragmentShaderSource");
    GetShaderManager()->AddVertexShader(texturedVertexShaderSource, "texturedVertexShaderSource");
    GetShaderManager()->AddVertexShader(texturedModelVertexShaderSource, "texturedModelVertexShaderSource");
    GetShaderManager()->AddFragmentShader(lineFragmentShaderSource, "lineFragmentShaderSource");
    GetShaderManager()->AddVertexShader(lineVertexShaderSource, "lineVertexShaderSource");
    GetShaderManager()->SetUpShaderProgram("lineVertexShaderSource", "lineFragmentShaderSource", "lineShader");
    GetShaderManager()->SetUpShaderProgram("texturedModelVertexShaderSource", "texturedFragmentShaderSource", "texturedPlaneShader");
}

void testScene::BeginDraw()
{
    ctScene::BeginDraw();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ++frameCounter;
    if(msecsCounter<1000)msecsCounter+=ctTime::GetTime()->GetDeltaTime();
    else {m_lastFPS=frameCounter; msecsCounter = 0;frameCounter=0;}

    //DrawText(QPointF(30,30), QString::number(m_lastFPS));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void testScene::Draw()
{
    ctScene::Draw();
    QMatrix4x4 matrix;
    matrix.ortho((0 - GetWindow()->width()/2), (GetWindow()->width()/2), (GetWindow()->height()/2), (0 - GetWindow()->height()/2), 0, 10000.0f);
    //matrix.perspective(60, 4.0/3.0, 0.1, 1000.0);
    matrix.translate(0, 0 , -50);
    //matrix.rotate(m_frame/*100.0f * m_frame / screen()->refreshRate()*/, 0, 1, 0);
    //qDebug()<<m_frame;
    //m_plane->GetTransform()->RotateByY(0.01f);//.GetMatrix().rotate(m_frame, 0, 1, 0);
    //ShowMatrix(m_plane->GetTransform()->GetLocalTransformMatrix().GetMatrix());
    m_plane->SetProjectionMatrix(matrix);
    m_plane2->SetProjectionMatrix(matrix);
    //ctWindow::RenderScene();
}

void testScene::EndDraw()
{
    ctScene::EndDraw();
    m_frame+=1.0f;
    if(m_frame > 360) m_frame = m_frame - 360;
    ctTime::GetTime()->Update();
    GetWindow()->DrawText(QPointF(30,30), QString::number(m_lastFPS));
    GetWindow()->DrawText(QPointF(30, 60), m_isClicked);
}
void testScene::Update()
{
    ctScene::Update();

    if(GetWindow()->GetInput()->GetEvents(ctInputEvent::IEF_MOUSE_BUTTON_PRESS).size() > 0)
    {
        QVector3D tmp;//GetWindow()->GetInput()->GetEvents(ctInputEvent::IEF_MOUSE_BUTTON_PRESS)[0].GetMouseEvent();
        tmp.setX(GetWindow()->GetInput()->GetEvents(ctInputEvent::IEF_MOUSE_BUTTON_PRESS)[0].GetMouseEvent().x());
        tmp.setY(GetWindow()->GetInput()->GetEvents(ctInputEvent::IEF_MOUSE_BUTTON_PRESS)[0].GetMouseEvent().y());
        tmp.setZ(1);
        tmp.setX(tmp.x() - (GetWindow()->width()/2));
        tmp.setY(tmp.y() - (GetWindow()->height()/2));

        qDebug()<<"Presed x: "<< tmp.x() << " y: "<<tmp.y();
        m_isClicked = QString("Ispresed");
    }
    if(GetWindow()->GetInput()->GetEvents(ctInputEvent::IEF_MOUSE_BUTTON_RELEASE).size() > 0)
    {
        qDebug()<<"released";
        m_isClicked = QString("not");
    }
}
