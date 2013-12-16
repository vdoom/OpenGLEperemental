#include <QtGui/QScreen>
#include "testappwindow.h"
#include "shaders.h"
#include "ctShaderManager.h"
#include "ctTime.h"
#include "ctPlane.h"
#include "shaders.h"
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QtOpenGL>
#include <QtOpenGL/QGLFormat>
#include "testscene.h"

void testAppWindow::ShowMatrix(QMatrix4x4 t_mat)
{
    qDebug()<<t_mat(0,0)<<" "<<t_mat(0,1)<<" "<<t_mat(0,2)<<" "<<t_mat(0,3);
    qDebug()<<t_mat(1,0)<<" "<<t_mat(1,1)<<" "<<t_mat(1,2)<<" "<<t_mat(1,3);
    qDebug()<<t_mat(2,0)<<" "<<t_mat(2,1)<<" "<<t_mat(2,2)<<" "<<t_mat(2,3);
    qDebug()<<t_mat(3,0)<<" "<<t_mat(3,1)<<" "<<t_mat(3,2)<<" "<<t_mat(3,3);
}

testAppWindow::testAppWindow(QWindow *parent) : ctWindow(parent)
{
    m_lastFPS = 0;
}

testAppWindow::testAppWindow(QOpenGLContext *t_context, QWindow *parent) : ctWindow(t_context, parent)
{
    m_lastFPS = 0;
}

testAppWindow::~testAppWindow()
{

}

void testAppWindow::initialize()
{
    ctWindow::initialize();

    qDebug()<<"init";
    SetDefault(m_context);
    m_plane2 = new ctPlane(GetShaderManager(), 0, m_context, QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    m_plane = new ctPlane(GetShaderManager(), 0, m_context, QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    m_plane2->InitShader("texturedPlaneShader");
    m_plane->InitShader("texturedPlaneShader");
    m_plane2->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    m_plane->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    m_plane2->GetTransform()->RotateByX(0.2f);
    m_plane2->GetTransform()->RotateByX(90.0f);
    m_plane2->GetTransform()->RotateByZ(90.0f);
    m_plane->GetTransform()->RotateByZ(0.2f);
    m_plane2->GetTransform()->Move(QVector3D(1,0,-1));
    m_plane->GetTransform()->Move(QVector3D(2,2,3));
    m_plane2->GenerateCompleteBuffer();
    m_plane->GenerateCompleteBuffer();
    m_plane2->GetTransform()->SetParent(m_plane->GetTransform());

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width(), height());
    if(!ctTime::GetTime())
    {qDebug()<<"Fuck\n";}
    m_frame = 0;

    SetScene(new testScene());
    GetScene()->SetShaderManager(GetShaderManager());
    GetScene()->AddObject(m_plane);
    GetScene()->AddObject(m_plane2);
}

void testAppWindow::render()
{
    ctWindow::render();
    //Draw();
    //renderLater();
}

void testAppWindow::SetDefault(QOpenGLContext *t_context)
{
    ctWindow::SetDefault(t_context);

    //SetShaderManager(new ctShaderManager());
    GetShaderManager()->AddFragmentShader(fragmentShaderSource, "fragmentShaderSource");
    GetShaderManager()->AddVertexShader(vertexShaderSource, "vertexShaderSource");
    GetShaderManager()->AddFragmentShader(texturedFragmentShaderSource, "texturedFragmentShaderSource");
    GetShaderManager()->AddVertexShader(texturedVertexShaderSource, "texturedVertexShaderSource");
    GetShaderManager()->AddVertexShader(texturedModelVertexShaderSource, "texturedModelVertexShaderSource");
    GetShaderManager()->SetUpShaderProgram("texturedModelVertexShaderSource", "texturedFragmentShaderSource", "texturedPlaneShader");
}

void testAppWindow::BeginRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ++frameCounter;
    if(msecsCounter<1000)msecsCounter+=ctTime::GetTime()->GetDeltaTime();
    else {m_lastFPS=frameCounter; msecsCounter = 0;frameCounter=0;}
    DrawText(QPointF(30,30), QString::number(m_lastFPS));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void testAppWindow::RenderScene()
{
    QMatrix4x4 matrix;
    matrix.perspective(60, 4.0/3.0, 0.1, 1000.0);
    matrix.translate(0, -1.5 , -15);
    //matrix.rotate(m_frame/*100.0f * m_frame / screen()->refreshRate()*/, 0, 1, 0);
    //qDebug()<<m_frame;
    m_plane->GetTransform()->RotateByY(0.01f);//.GetMatrix().rotate(m_frame, 0, 1, 0);
    //ShowMatrix(m_plane->GetTransform()->GetLocalTransformMatrix().GetMatrix());
    m_plane->SetProjectionMatrix(matrix);
    m_plane2->SetProjectionMatrix(matrix);
    ctWindow::RenderScene();
}

void testAppWindow::EndRender()
{
    m_frame+=1.0f;
    if(m_frame > 360) m_frame = m_frame - 360;
    ctTime::GetTime()->Update();
}

