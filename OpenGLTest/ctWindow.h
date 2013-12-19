#ifndef CTWINDOW_H
#define CTWINDOW_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QPainter>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class ctScene;
class ctShaderManager;
class ctInput;

class ctWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    ctScene * m_scene;
    ctShaderManager * m_shaderManager;
    ctInput* m_input;
    bool m_update_pending;
protected:
    QOpenGLContext * m_context;
    QOpenGLPaintDevice *m_device;

    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);
    virtual void SetDefault(QOpenGLContext *t_context = 0);
    virtual void BeginRenderScene();
    virtual void RenderScene();
    virtual void EndRenderScene();
public:
    explicit ctWindow(QWindow *parent = 0);
    explicit ctWindow(QOpenGLContext * t_context, QWindow *parent = 0);
    virtual ~ctWindow();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    virtual void Draw();

    QOpenGLContext * GetOpenGLContext() const;
    QOpenGLPaintDevice * GetOpenGLDevice() const;

    void SetScene(ctScene* t_scene);
    ctScene * GetScene() const;

    ctInput * GetInput() const;

    void SetShaderManager(ctShaderManager * t_shaderManager);
    ctShaderManager * GetShaderManager() const;

    void DrawText(QPointF, QString);

public slots:
    void renderLater();
    void renderNow();
};

#endif // CTWINDOW_H
