/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

#include "shadermanager.h"
#include "axis.h"
#include "boxtextured.h"
#include "plane.h"
#include "shaders.h"
#include "ctPlane.h"
void ShowMatrix(QMatrix4x4 t_mat)
{
    qDebug()<<t_mat(0,0)<<" "<<t_mat(0,1)<<" "<<t_mat(0,2)<<" "<<t_mat(0,3);
    qDebug()<<t_mat(1,0)<<" "<<t_mat(1,1)<<" "<<t_mat(1,2)<<" "<<t_mat(1,3);
    qDebug()<<t_mat(2,0)<<" "<<t_mat(2,1)<<" "<<t_mat(2,2)<<" "<<t_mat(2,3);
    qDebug()<<t_mat(3,0)<<" "<<t_mat(3,1)<<" "<<t_mat(3,2)<<" "<<t_mat(3,3);
}
class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize();
    void render();

private:
    ShaderManager *m_shaderManager;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
    Axis** axis;
    BoxTextured* box;
    Plane* plane;
    ctPlane * trPlane;
};

TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
{
}

void TriangleWindow::initialize()
{
    m_shaderManager = new ShaderManager();
    m_shaderManager->AddFragmentShader(fragmentShaderSource);
    m_shaderManager->AddVertexShader(vertexShaderSource);
    m_shaderManager->AddFragmentShader(texturedFragmentShaderSource);
    m_shaderManager->AddVertexShader(texturedVertexShaderSource);
    m_shaderManager->AddVertexShader(texturedModelVertexShaderSource);
    //m_shaderManager->AddFragmentShader(materialFragmentShaderSource);
   // m_shaderManager->AddVertexShader(materialVertexShaderSource);

    //m_shaderManager->SetUpShaderProgram(0, 0);
    //m_matrixUniform = m_shaderManager->GetCurrentShaderProgram()->uniformLocation("matrix");
    axis = new Axis * [3];
    axis[0] = new Axis(QVector3D(2.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.3f, 0.3f), m_shaderManager);
    axis[1] = new Axis(QVector3D(0.0f, 2.0f, 0.0f), QVector3D(0.3f, 1.0f, 0.3f), m_shaderManager);
    axis[2] = new Axis(QVector3D(0.0f, 0.0f, 2.0f), QVector3D(0.3f, 0.3f, 1.0f), m_shaderManager);
    axis[0]->InitShaders();
    axis[1]->InitShaders();
    axis[2]->InitShaders();
    box = new BoxTextured(m_shaderManager);
    box->LoadTexture("/Users/volodymyrkuksynok/Downloads/texturen.tga");
    box->InitShaderProgram();
    //plane = new Plane(m_shaderManager, QVector3D(2,0,2), QVector3D(-2,0,-2), Plane::Textured);
    //plane->InitShader();
    //plane->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    trPlane = new ctPlane(m_shaderManager, QVector3D(2,0,2), QVector3D(-2,0,-2), ctPlane::Textured);//new ctPlane(m_shaderManager, QVector3D(2,0,2), QVector3D(-2,0,-2), Plane::Textured);
    //trPlane->InitShader();
    trPlane->SetTexture("/Users/volodymyrkuksynok/Downloads/cat_hungry.png");
    //ctTransform tmp;
    //trPlane->GetTransform().GetGlobalTransformMatrix();
    //::ShowMatrix(trPlane->GetTransform()->GetGlobalTransformMatrix().GetMatrix()); //GetGlobalTransformMatrix().GetMatrix());
    //trPlane->GetTransform()->Move(QVector3D(2,3,2));
    trPlane->GetTransform()->RotateByX(0.2f);
    trPlane->GetTransform()->Move(QVector3D(2,2,3));
    //tmp.Move(QVector3D(2,3,2));
    //::ShowMatrix(trPlane->GetTransform()->GetGlobalTransformMatrix().GetMatrix());
    //plane->CreateTexture("/Users/volodymyrkuksynok/Downloads/texturen.tga", "TGA");
    //plane->GenerateCompleteBuffer();
    //trPlane->GenerateCompleteBuffer();
    trPlane->Init();

    //trPlane->GetTransform()->Move(QVector3D(2,3,2));
    //trPlane->GetTransform()->RotateByX(0.2f);
    //tmp.Move(QVector3D(2,3,2));
    //::ShowMatrix(trPlane->GetTransform()->GetGlobalTransformMatrix().GetMatrix());
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    //glClearDepth(1.0f);
    //glClearDepth(2000.0);
//    glEnable(GL_DEPTH_TEST);  // Enables Depth Testing
//    glDepthFunc(GL_LESS);     // The Type Of Depth Test To Do
//    glShadeModel(GL_SMOOTH);  // Enables Smooth Color Shading
//     glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glViewport(0, 0, width(), height());
}

void TriangleWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.perspective(60, 4.0/3.0, 0.1, 100.0);
    matrix.translate(0, -1.5f , -5);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    //box->Draw(matrix);
    //plane->Draw(matrix);

    for(int i = 0; i < 3; ++i)
    {
        axis[i]->Draw(matrix);
    }
    trPlane->Draw(matrix);

    ++m_frame;
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    //format.setStereo(true);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}


