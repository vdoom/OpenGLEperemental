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
   // m_lastFPS = 0;
}

testAppWindow::testAppWindow(QApplication * t_QApp, QWindow *parent) : ctWindow(t_QApp, parent)
{
   // m_lastFPS = 0;
}

//testAppWindow::testAppWindow(QOpenGLContext *t_context, QWindow *parent) : ctWindow(t_context, parent)
//{
////    m_lastFPS = 0;
//}

testAppWindow::testAppWindow(QOpenGLContext *t_context, QApplication *t_QApp, QWindow *parent) : ctWindow(t_context, t_QApp, parent)
{
//    m_lastFPS = 0;
}

testAppWindow::~testAppWindow()
{

}

void testAppWindow::initialize()
{
    SetDefault(m_context);
    SetScene(new testScene(GetShaderManager(), GetOpenGLContext()));
    //GetScene()->Init();
    GetScene()->SetShaderManager(GetShaderManager());
    GetScene()->SetWindow(this);

    ctWindow::initialize();

    qDebug()<<"init";

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
}

void testAppWindow::BeginRenderScene()
{
    ctWindow::BeginRenderScene();
}

void testAppWindow::RenderScene()
{
    ctWindow::RenderScene();
}

void testAppWindow::EndRenderScene()
{
    ctWindow::EndRenderScene();

}

