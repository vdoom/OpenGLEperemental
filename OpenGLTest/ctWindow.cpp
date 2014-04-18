#include "ctWindow.h"
#include "ctShaderManager.h"
#include "ctScene.h"
#include "ctInput.h"
#include "ctGLWidget.h"

#include <QApplication>
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QtOpenGL>
#include <QtOpenGL/QGLFormat>
#include <QDebug>

ctWindow::ctWindow(QWindow *parent) : QWindow(parent), m_context(0), m_device(0)
{
    //setSurfaceType(QWindow::OpenGLSurface);
    SetDefault();
}

ctWindow::ctWindow(QApplication * t_QApp, QWindow *parent) : QWindow(parent), m_context(0), m_device(0), m_QApp(t_QApp)
{
    SetDefault();
}

//ctWindow::ctWindow(QOpenGLContext *t_context, QWindow *parent) : QWindow(parent), m_context(t_context), m_device(0)
//{
//    //setSurfaceType(QWindow::OpenGLSurface);
//    SetDefault(t_context);
//}

ctWindow::ctWindow(QOpenGLContext *t_context, QApplication * t_QApp,  QWindow *parent) : QWindow(parent), m_context(t_context), m_device(0), m_QApp(t_QApp)
{
    //setSurfaceType(QWindow::OpenGLSurface);
    SetDefault(t_context);
}

ctWindow::~ctWindow()
{
    qDebug()<<"Destroy Window";
    delete m_scene;
    delete m_shaderManager;
    delete m_context;
    delete m_device;
    delete m_input;


}

bool ctWindow::event(QEvent *event)
{
    if(m_input)
        m_input->event(event);
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        //qDebug()<<"UpdateRequest";
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
    {
        m_device = new QOpenGLPaintDevice;
        m_device->setSize(size());
    }

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    //QPainter painter(m_device);
    //render(&painter);
    Draw();//RenderScene();
    renderLater();
}

void ctWindow::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void ctWindow::initialize()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;
    m_device->setSize(size());

    m_GLWidget = new ctGLWidget();
    qDebug()<<"Init GLWidget";
    if(m_scene)
    {
        m_scene->Init();
    }
    //Initialization;
}

QOpenGLContext * ctWindow::GetOpenGLContext() const
{
    return m_context;
}

void ctWindow::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
        //()<<"UpdateRequest";
    }
}

void ctWindow::renderNow()
{
    //qDebug()<<"RenderNow";
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        QGLFormat format = QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer);
        QGLFormat::setDefaultFormat(format);
        QSurfaceFormat t_format = requestedFormat();
        //t_format.setSamples(16);
        //t_format.setDepthBufferSize(24);
        //setFormat(t_format);
        m_context->setFormat(t_format);
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
        renderLater();
}

void ctWindow::SetScene(ctScene* t_scene)
{
    m_scene = t_scene;
}

ctScene * ctWindow::GetScene() const
{
    return m_scene;
}

ctInput * ctWindow::GetInput() const
{
    return m_input;
}

void ctWindow::RenderScene()
{
    if(m_scene)
        m_scene->Draw();
}

void ctWindow::BeginRenderScene()
{
    if(m_scene)
        m_scene->BeginDraw();
}

void ctWindow::EndRenderScene()
{
    if(m_scene)
        m_scene->EndDraw();
}

void ctWindow::Draw()
{
    //-----temporary-soluton-----
    if(m_scene)
    {
        m_scene->Update();
        m_input->Update();
    }
    //---------------------------
    if(m_GLWidget)
    {
        m_GLWidget->updateGL();
    }
//    BeginRenderScene();

//    RenderScene();

//    EndRenderScene();
}

void ctWindow::SetShaderManager(ctShaderManager *t_shaderManager)
{
    m_shaderManager = t_shaderManager;
}

ctShaderManager* ctWindow::GetShaderManager() const
{
    return m_shaderManager;
}

QApplication* ctWindow::GetQApplication() const
{
    return m_QApp;
}

qreal ctWindow::GetDevicePixelRatioCoff() const
{
    return m_QApp->devicePixelRatio();
}

int ctWindow::GetWidth() const
{
    return width() * GetDevicePixelRatioCoff();
}

int ctWindow::GetHeight() const
{
    return height() * GetDevicePixelRatioCoff();
}

void ctWindow::SetDefault(QOpenGLContext *t_context)
{
    SetScene(0);
    setSurfaceType(QWindow::OpenGLSurface);
    if(!t_context)
        m_shaderManager = new ctShaderManager();
    else
        m_shaderManager = new ctShaderManager(t_context);

    m_update_pending = false;

    m_input = new ctInput(this);

    m_defaultHeight = 768;
    m_defaultWidth = 1024;
	m_startupResolution = QVector2D(m_defaultWidth, m_defaultHeight);

    //m_GLWidget = new ctGLWidget();
}

void ctWindow::DrawText(QPointF t_pos, QString t_str)
{
    QPainter painter(m_device);
    painter.setPen(Qt::green);
    painter.drawText(t_pos, t_str);
}

QVector2D ctWindow::GetStartupResolution() const
{
    return m_startupResolution;
}

void ctWindow::SetResolution(int t_width, int t_height)
{
    m_startupResolution = QVector2D(t_width, t_height);
    resize(t_width, t_height);
}

int ctWindow::GetDefaultHeight() const
{
    return m_defaultHeight;
}

int ctWindow::GetDefaultWidth() const
{
    return m_defaultWidth;
}


float ctWindow::GetWidthScale() const
{
    return ((float)GetDefaultWidth() / (float)(GetWidth()));
}

float ctWindow::GetHeightScale() const
{
    return ((float)GetDefaultHeight() / (float)(GetHeight()));
}
