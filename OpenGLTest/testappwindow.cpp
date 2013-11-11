#include "testappwindow.h"

testAppWindow::testAppWindow(QWindow *parent) : ctWindow(parent)
{}

testAppWindow::testAppWindow(QOpenGLContext *t_context, QWindow *parent) : ctWindow(t_context, parent)
{}

testAppWindow::~testAppWindow()
{

}

void testAppWindow::initialize()
{

}

void testAppWindow::render()
{

}
