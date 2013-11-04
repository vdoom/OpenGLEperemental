#ifndef CTWINDOW_H
#define CTWINDOW_H

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class ctWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
private:
protected:
    QOpenGLContext * m_context;
    QOpenGLPaintDevice *m_device;

    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);
public:
    explicit ctWindow(QWindow *parent = 0);
    explicit ctWindow(QOpenGLContext * t_context, QWindow *parent = 0);
    virtual ~ctWindow();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();

    QOpenGLContext * GetOpenGLContext() const;

public slots:
    void renderLater();
    void renderNow();
};

#endif // CTWINDOW_H
