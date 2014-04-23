#ifndef TESTAPPWINDOW_H
#define TESTAPPWINDOW_H

#include "ctWindow.h"


class ctPlane;
class QMatrix4x4;

class testAppWindow : public ctWindow
{
private:
//    float m_frame;
//    int m_lastFPS;
//    int frameCounter;
//    int msecsCounter;
//    ctPlane * m_plane;
//    ctPlane * m_plane2;
private:
    virtual void SetDefault(QGLContext *t_context = 0);
    virtual void BeginRenderScene();
    virtual void EndRenderScene();
    virtual void RenderScene();
public:
    explicit testAppWindow(QWindow *parent = 0);
    explicit testAppWindow(QApplication * t_QApp, QWindow *parent = 0);
    explicit testAppWindow(QGLContext * t_context, QApplication * t_QApp = 0, QWindow *parent = 0);
    virtual ~testAppWindow();

    virtual void initialize();
    virtual void render();

    void ShowMatrix(QMatrix4x4 t_mat);
};

#endif // TESTAPPWINDOW_H
