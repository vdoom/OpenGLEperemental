#include <QGLFunctions>
#include "ctGLWidget.h"
#include "ctScene.h"
#include <QDebug>

ctGLWidget::ctGLWidget(ctScene* t_scene) : QGLWidget()
{
    m_scene = t_scene;
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoBufferSwap(false);
    //m_showBubbles = true;
    //setMinimumSize(300, 250);
    makeCurrent();
}

void ctGLWidget::paintGL()
{
makeCurrent();
    //QPainter painter;
   // painter.begin(this);

    //painter.beginNativePainting();

    glClearColor(0.0, 0.0, 1.0, 0.0);

    if(m_scene)
    {
        m_scene->BeginDraw();
        m_scene->Draw();
        m_scene->EndDraw();
        //qDebug()<<"DrawGL";
    }
    makeCurrent();
    //painter.drawText(20, 40, framesPerSecond + " fps");
    //painter.endNativePainting();
    //painter.end();
   swapBuffers();
//    else
//    {qDebug()<<"HasentScene";}
//    glClearColor(1.0, 0.0, 1.0, 0.0);
//    qDebug()<<"Clear";
}

void ctGLWidget::initializeGL()
{
    makeCurrent();
    glClearColor(0.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    qDebug()<<"\n\nQGLContext is valid11: \n\n"<< isValid();

//    if(m_scene)
//    {
//        m_scene->Init();
//    }
}

void ctGLWidget::SetScene(ctScene * t_scene)
{
    m_scene = t_scene;
}

ctScene* ctGLWidget::GetScene()
{
    return m_scene;
}
