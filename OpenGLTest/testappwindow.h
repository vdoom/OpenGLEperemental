#ifndef TESTAPPWINDOW_H
#define TESTAPPWINDOW_H

#include "ctWindow.h"

class testAppWindow : public ctWindow
{
public:
    explicit testAppWindow(QWindow *parent = 0);
    explicit testAppWindow(QOpenGLContext * t_context, QWindow *parent = 0);
    virtual ~testAppWindow();

    virtual void initialize();
    virtual void render();
};

#endif // TESTAPPWINDOW_H
