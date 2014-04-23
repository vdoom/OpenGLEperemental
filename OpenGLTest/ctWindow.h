#ifndef CTWINDOW_H
#define CTWINDOW_H

//#include <QtGui/QWindow>
#include <QMainWindow>
//#include <QtGui/QOpenGLFunctions>
#include <QGLContext>
#include <QPainter>
#include <QVector2D>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
class QApplication;
QT_END_NAMESPACE

class ctScene;
class ctShaderManager;
class ctInput;
class ctGLWidget;

class ctWindow : public QMainWindow
{
    Q_OBJECT
private:
    QApplication * m_QApp;
    ctScene * m_scene;
    ctShaderManager * m_shaderManager;
    ctInput* m_input;
    QVector2D m_startupResolution;
    int m_defaultWidth, m_defaultHeight;
    bool m_update_pending;

protected:
    //QGLContext * m_context;
    QOpenGLPaintDevice *m_device;
    ctGLWidget * m_GLWidget;

    bool event(QEvent *event);
    //void exposeEvent(QExposeEvent *event);
    virtual void SetDefault(QGLContext *t_context = 0);
    virtual void BeginRenderScene();
    virtual void RenderScene();
    virtual void EndRenderScene();
public:
    explicit ctWindow(QWindow *parent = 0);
    explicit ctWindow(QApplication * t_QApp, QWindow *parent = 0);
    //explicit ctWindow(QOpenGLContext * t_context, QWindow *parent = 0);
    explicit ctWindow(QGLContext * t_context, QApplication * t_QApp = 0, QWindow *parent = 0);
    virtual ~ctWindow();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    virtual void Draw();

    QGLContext * GetOpenGLContext();
    //QOpenGLPaintDevice * GetOpenGLDevice() const;

    void SetScene(ctScene* t_scene);
    ctScene * GetScene() const;

    ctInput * GetInput() const;

    void SetShaderManager(ctShaderManager * t_shaderManager);
    ctShaderManager * GetShaderManager() const;

    QApplication * GetQApplication() const;
    qreal GetDevicePixelRatioCoff() const;
    int GetWidth() const;
    int GetHeight() const;
    QVector2D GetStartupResolution() const;
    void DrawText(QPointF, QString);
    void SetResolution(int t_width, int t_height);
    int GetDefaultWidth() const;
    int GetDefaultHeight() const;
    float GetWidthScale() const;
    float GetHeightScale() const;

public slots:
    void renderLater();
    void renderNow();
};

#endif // CTWINDOW_H
