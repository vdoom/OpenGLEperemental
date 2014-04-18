#include "ctGLWidget.h"
#include "ctScene.h"

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
    if(m_scene)
    {
        m_scene->BeginDraw();
        m_scene->Draw();
        m_scene->EndDraw();
    }
}

void ctGLWidget::initializeGL()
{}

void ctGLWidget::SetScene(ctScene * t_scene)
{
    m_scene = t_scene;
}

ctScene* ctGLWidget::GetScene()
{
    return m_scene;
}
