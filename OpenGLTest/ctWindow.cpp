#include "ctWindow.h"
#include "ctShaderManager.h"
#include "ctScene.h"
#include "ctInput.h"


#include <QApplication>
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>

#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QtOpenGL>
#include <QtOpenGL/QGLFormat>
#include <QDebug>

#include <QTimer>

ctWindow::ctWindow(QWindow *parent) : QWindow(parent), m_context(0), m_device(0), m_input(0)
{
    //setSurfaceType(QWindow::OpenGLSurface);
m_input = new ctInput(this);
m_player = new QMediaPlayer(this);
connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(MusickStoped(QMediaPlayer::State)));

//    m_GLWidget = new ctGLWidget();
 //   QGroupBox * groupBox = new QGroupBox(this);
 //   setCentralWidget(groupBox);
 //   groupBox->setTitle("OpenGL ES Example");
 //   QGridLayout *layout = new QGridLayout(groupBox);
 //   layout->addWidget(m_GLWidget,1,0,8,1);
 //   groupBox->setLayout(layout);

    SetDefault();
    screen()->setOrientationUpdateMask(Qt::LandscapeOrientation|Qt::InvertedLandscapeOrientation);

    m_settings = new QSettings(QString("Kuksynok_v"), QString("Hard_Hanoi"));
}

ctWindow::ctWindow(QApplication * t_QApp, QWindow *parent) : QWindow(parent), m_context(0), m_device(0), m_QApp(t_QApp), m_input(0)
{
    m_input = new ctInput(this);
    m_player = new QMediaPlayer(this);
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(MusickStoped(QMediaPlayer::State)));

    QTimer *timer = new QTimer(this);
    timer->setInterval(18);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start();

    connect(m_QApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)), this, SLOT(StateChange(Qt::ApplicationState)));

    SetDefault();
    screen()->setOrientationUpdateMask(Qt::LandscapeOrientation|Qt::InvertedLandscapeOrientation);
    m_settings = new QSettings(QString("Kuksynok_v"), QString("Hard_Hanoi"));
}

//ctWindow::ctWindow(QOpenGLContext *t_context, QWindow *parent) : QWindow(parent), m_context(t_context), m_device(0)
//{
//    //setSurfaceType(QWindow::OpenGLSurface);
//    SetDefault(t_context);
//}

ctWindow::ctWindow(QOpenGLContext *t_context, QApplication * t_QApp,  QWindow *parent) :QWindow(parent), m_context(0), m_device(0), m_QApp(t_QApp), m_input(0)
{
    //setSurfaceType(QWindow::OpenGLSurface);
    m_input = new ctInput(this);
    m_player = new QMediaPlayer(this);
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(MusickStoped(QMediaPlayer::State)));

    connect(m_QApp, SIGNAL(applicationStateChanged(Qt::ApplicationState)), this, SLOT(StateChange(Qt::ApplicationState)));
    SetDefault(t_context);
    screen()->setOrientationUpdateMask(Qt::LandscapeOrientation|Qt::InvertedLandscapeOrientation);
    m_settings = new QSettings(QString("Kuksynok_v"), QString("Hard_Hanoi"));
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
    if(event->type() == QEvent::KeyPress)
    {

        QKeyEvent* tmp = static_cast<QKeyEvent *>(event);
        if(tmp->key() == Qt::Key_Back)
        {
            qDebug()<<"\n\n\n\nKeyBack\n\n\n";
            m_onPressBack.Call();
        }
    }
    if(m_input)
        m_input->event(event);
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
    //renderLater();

    static bool ss = false;
    if(!ss)
    {
        ss = true;
        qDebug()<<"dddd";
    }
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

        if(!m_input)
            m_input = new ctInput(this);

        if(m_scene)
        {
            m_scene->Init();
        }
}

QOpenGLContext * ctWindow::GetOpenGLContext()
{
    return m_context;
}

//void ctWindow::renderLater()
//{
//    if (!m_update_pending)
//    {
//        m_update_pending = true;
//        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
//        //()<<"UpdateRequest";
//    }
//}

void ctWindow::renderNow()
{
    //qDebug()<<"RenderNow";
    if (!isExposed())
        return;

    static bool needsInitialize = false;

    if (!m_context)
    {
        m_context = new QOpenGLContext(this);
        QSurfaceFormat t_format = requestedFormat();
        m_context->setFormat(t_format);
        m_context->create();

	needsInitialize = true;
  }

    m_context->makeCurrent(this);

    if (needsInitialize)
    {
        needsInitialize = false;
        //initializeOpenGLFunctions();
        qDebug()<<"Version: "<<(const char*)glGetString(GL_VERSION);//tmp;
        qDebug()<<"Renderer: "<<(const char*)glGetString(GL_RENDERER);
        qDebug()<<"Shaders: "<<(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        qDebug()<<"Vendor: "<<(const char*)glGetString(GL_VENDOR);
        initialize();
    }

    //if(m_GLWidget) m_GLWidget->updateGL();
    render();

    m_context->swapBuffers(this);

    //if (m_animating)
        //renderLater();
}

void ctWindow::SetScene(ctScene* t_scene)
{
    m_scene = t_scene;
 //   m_GLWidget->SetScene(t_scene);
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

    BeginRenderScene();

    RenderScene();

    EndRenderScene();
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

qDebug()<<"SetDefault";
    //m_GLWidget->updateGL();

    SetScene(0);
    setSurfaceType(QWindow::OpenGLSurface);
    if(t_context)
        m_shaderManager = new ctShaderManager();
    else
        m_shaderManager = new ctShaderManager(GetOpenGLContext());

    m_update_pending = false;



    m_defaultHeight = 768;
    m_defaultWidth = 1024;
	m_startupResolution = QVector2D(m_defaultWidth, m_defaultHeight);

    //m_GLWidget = new ctGLWidget();
}

void ctWindow::DrawText(QPointF t_pos, QString t_str)
{
    QPainter painter(m_device);
    //painter.begin(m_GLWidget);
    painter.setPen(Qt::green);
    painter.drawText(t_pos, t_str);
    //painter.end();
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

void ctWindow::StateChange(Qt::ApplicationState state)
{
    qDebug()<<"StateChange";
    switch(state)
    {
        case Qt::ApplicationSuspended:
        {
            qDebug()<<"ApplicationSuspended";
            if(m_scene)
            {m_scene->Freeze();}
            break;
        }
        case Qt::ApplicationHidden:
        {
            qDebug()<<"ApplicationHidden";
            if(m_scene)
            {m_scene->Freeze();}
            break;
        }
        case Qt::ApplicationInactive:
        {
            qDebug()<<"ApplicationInactive";
            if(m_scene)
            {m_scene->Freeze();}
            break;
        }
        case Qt::ApplicationActive:
        {
            qDebug()<<"ApplicationActive";
            if(m_scene)
            {m_scene->Unfreeze();}
            break;
        }
    }
}

QMediaPlayer* ctWindow::GetMediaPlayer()
{
    return m_player;
}

void ctWindow::MusickStoped(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::StoppedState)
    {
        m_player->play();
    }
}

QSettings* ctWindow::GetSettings()
{
    return m_settings;
}

ctFastDelegat* ctWindow::GetDelegatOnPressBack()
{
    return &m_onPressBack;
}
