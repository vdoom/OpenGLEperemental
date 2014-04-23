#include <QGLFunctions>
#include "ctGLWidget.h"
#include "ctScene.h"
#include <QDebug>

ctGLWidget::ctGLWidget(QWidget *parent) : QGLWidget(parent)
{
    m_scene = 0;
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoBufferSwap(false);
    //m_showBubbles = true;
    setMinimumSize(300, 250);
    makeCurrent();
}

void ctGLWidget::paintGL()
{
    //qDebug()<<"repaint";
    glClearColor(1.0, 0.0, 1.0, 0.0);
    if(m_scene)
    {
        m_scene->BeginDraw();
        m_scene->Draw();
        m_scene->EndDraw();
    }
    //glClearColor(1.0, 0.0, 0.0, 0.0);
}

void ctGLWidget::initializeGL()
{
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    qDebug()<<"QGLContext is valid: "<< isValid();
}

void ctGLWidget::SetScene(ctScene * t_scene)
{
    m_scene = t_scene;
}

ctScene* ctGLWidget::GetScene()
{
    return m_scene;
}
