#include "testappwindow.h"
#include "shaders.h"
#include "ctShaderManager.h"

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

void testAppWindow::SetDefault(QOpenGLContext *t_context)
{
    ctWindow::SetDefault(t_context);

    GetShaderManager()->AddFragmentShader(fragmentShaderSource, "fragmentColored");
    GetShaderManager()->AddVertexShader(vertexShaderSource, "vertexColored");
    GetShaderManager()->AddFragmentShader(texturedFragmentShaderSource, "fragmentTextured");
    GetShaderManager()->AddVertexShader(texturedVertexShaderSource, "vertexTextured");
    GetShaderManager()->AddVertexShader(texturedModelVertexShaderSource, "vertexTexturedModel");
}

void testAppWindow::BeginRender()
{}

void testAppWindow::EndRender()
{}
