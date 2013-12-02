#ifndef TESTAPPWINDOW_H
#define TESTAPPWINDOW_H

#include "ctWindow.h"

class ctPlane;

class testAppWindow : public ctWindow
{
private:
    int m_frame;
    int m_lastFPS;
    int frameCounter;
    int msecsCounter;
    ctPlane * m_plane;
private:
    virtual void SetDefault(QOpenGLContext *t_context = 0);
    virtual void BeginRender();
    virtual void EndRender();
    virtual void RenderScene();
public:
    explicit testAppWindow(QWindow *parent = 0);
    explicit testAppWindow(QOpenGLContext * t_context, QWindow *parent = 0);
    virtual ~testAppWindow();

    virtual void initialize();
    virtual void render();
};

#endif // TESTAPPWINDOW_H
