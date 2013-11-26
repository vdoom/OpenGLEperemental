#include <QtGui/QScreen>
#include "testappwindow.h"
#include "shaders.h"
#include "ctShaderManager.h"
#include "ctTime.h"
#include "ctPlane.h"
#include "shaders.h"

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
    //m_shaderManager = new ctShaderManager();

//    m_shaderManager->AddFragmentShader(fragmentShaderSource, "fragmentShaderSource");
//    m_shaderManager->AddVertexShader(vertexShaderSource, "vertexShaderSource");
//    m_shaderManager->AddFragmentShader(texturedFragmentShaderSource, "texturedFragmentShaderSource");
//    m_shaderManager->AddVertexShader(texturedVertexShaderSource, "texturedVertexShaderSource");
//    m_shaderManager->AddVertexShader(texturedModelVertexShaderSource, "texturedModelVertexShaderSource");
//    m_shaderManager->SetUpShaderProgram("texturedModelVertexShaderSource", "texturedFragmentShaderSource", "texturedPlaneShader");
    qDebug()<<"init";
    SetDefault(m_context);
    m_plane = new ctPlane(GetShaderManager(), 0, m_context, QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);
    m_plane->InitShader("texturedPlaneShader");
    m_plane->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    m_plane->GetTransform()->RotateByZ(0.2f);
    m_plane->GetTransform()->Move(QVector3D(2,2,3));
    m_plane->GenerateCompleteBuffer();

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width(), height());
    if(!ctTime::GetTime())
    {qDebug()<<"Fuck\n";}
}

void testAppWindow::render()
{
    //qDebug()<<"Render";
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 matrix;
    matrix.perspective(60, 4.0/3.0, 0.1, 100.0);
    matrix.translate(0, -1.5f , -5);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    //m_plane->DrawTextured(matrix);
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
    //QPainter m_painter(m_device);
    DrawText(QPointF(30,30), QString::number(m_lastFPS));
}

void testAppWindow::EndRender()
{
    ++m_frame;
    ctTime::GetTime()->Update();
}
