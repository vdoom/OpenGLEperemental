#include "ctWindow.h"

#include "ctScene.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QtOpenGL>
#include <QtOpenGL/QGLFormat>
#include <QDebug>

ctWindow::ctWindow(QWindow *parent) : QWindow(parent), m_context(0), m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

ctWindow::ctWindow(QOpenGLContext *t_context, QWindow *parent) : QWindow(parent), m_context(t_context), m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

ctWindow::~ctWindow()
{
    delete m_device;
}

bool ctWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void ctWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void ctWindow::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());
    QPainter painter(m_device);
    render(&painter);

}

void ctWindow::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void ctWindow::initialize()
{
    //Initialization;
}

QOpenGLContext * ctWindow::GetOpenGLContext() const
{
    return m_context;
}

void ctWindow::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void ctWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        QGLFormat format = QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
        //GLuint depthRenderbuffer;

        //QString tmp((const char*)glGetString(GL_VERSION));
        //GL_VENDOR, GL_RENDERER, GL_VERSION, or GL_SHADING_LANGUAGE_VERSION
        qDebug()<<"Version: "<<(const char*)glGetString(GL_VERSION);//tmp;
        qDebug()<<"Renderer: "<<(const char*)glGetString(GL_RENDERER);
        qDebug()<<"Shaders: "<<(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        qDebug()<<"Vendor: "<<(const char*)glGetString(GL_VENDOR);
        //        glGenRenderbuffers(1, &depthRenderbuffer);
        //                glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);

        //                // GL_DEPTH24_STENCIL8_OES: Set a depth buffer and a stencil buffer.
        //                // GL_DEPTH_COMPONENT16: Set a 16bits depth buffer.
        //                // GL_DEPTH_COMPONENT24_OES: Set a 24bits depth buffer.
        //                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 800, 600);
        //                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
    }

    render();

    m_context->swapBuffers(this);

    //if (m_animating)
    //    renderLater();
}

void ctWindow::SetScene(ctScene* t_scene)
{
    m_scene = t_scene;
}

ctScene * ctWindow::GetScene() const
{
    return m_scene;
}



