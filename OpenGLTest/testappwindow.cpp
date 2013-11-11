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

    m_shaderManager->AddFragmentShader(fragmentShaderSource, "fragmentColored");
    m_shaderManager->AddVertexShader(vertexShaderSource, "vertexColored");
    m_shaderManager->AddFragmentShader(texturedFragmentShaderSource, "fragmentTextured");
    m_shaderManager->AddVertexShader(texturedVertexShaderSource, "vertexTextured");
    m_shaderManager->AddVertexShader(texturedModelVertexShaderSource, "vertexTexturedModel");
}

void testAppWindow::BeginRender()
{}

void testAppWindow::EndRender()
{}
