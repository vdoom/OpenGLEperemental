#include "testappwindow.h"
#include "shaders.h"
#include "ctShaderManager.h"
#include "ctTime.h"

testAppWindow::testAppWindow(QWindow *parent) : ctWindow(parent)
{}

testAppWindow::testAppWindow(QOpenGLContext *t_context, QWindow *parent) : ctWindow(t_context, parent)
{}

testAppWindow::~testAppWindow()
{

}

void testAppWindow::initialize()
{
    ctWindow::initialize();
}

void testAppWindow::render()
{

}

void testAppWindow::SetDefault(QOpenGLContext *t_context)
{
    ctWindow::SetDefault(t_context);

    GetShaderManager()->AddFragmentShader(fragmentShaderSource, "fragmentColored");
    GetShaderManager()->AddVertexShader(vertexShaderSource, "vertexColored");
    GetShaderManager()->AddFragmentShader(texturedFragmentShaderSource, "fragmentTextured");
    GetShaderManager()->AddVertexShader(texturedVertexShaderSource, "vertexTextured");
    GetShaderManager()->AddVertexShader(texturedModelVertexShaderSource, "vertexTexturedModel");
}

void testAppWindow::BeginRender()
{
    ++frameCounter;
    if(msecsCounter<1000)msecsCounter+=ctTime::GetTime()->GetDeltaTime();
    else {m_lastFPS=frameCounter; msecsCounter = 0;frameCounter=0;}
    //QPainter m_painter(m_device);
    DrawText(QPointF(30,30), QString::number(m_lastFPS));
}

void testAppWindow::EndRender()
{
    ctTime::GetTime()->Update();
}
