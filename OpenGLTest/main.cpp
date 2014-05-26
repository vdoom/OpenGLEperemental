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

#include <QApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QOpenGLPaintDevice>

#include <QtCore/qmath.h>
#include <QProcess>//QGLWidget>
#include "shadermanager.h"
#include <QDesktopWidget>
#include <QResource>
#include <QSplashScreen>
//#include "axis.h"
//#include "boxtextured.h"
//#include "plane.h"
#include "shaders.h"
#include "ctPlane.h"
#include "ctTime.h"
#include "ctShaderManager.h"
#include "ctInput.h"
#include "testappwindow.h"

#include "QDebug"
#include "ctDelegat.h"
#include "ctFastDelegat.h"
//#include <functional>
//#include <iostream>
#include "ctRand.h"

void ShowMatrix(QMatrix4x4 t_mat)
{
    qDebug()<<t_mat(0,0)<<" "<<t_mat(0,1)<<" "<<t_mat(0,2)<<" "<<t_mat(0,3);
    qDebug()<<t_mat(1,0)<<" "<<t_mat(1,1)<<" "<<t_mat(1,2)<<" "<<t_mat(1,3);
    qDebug()<<t_mat(2,0)<<" "<<t_mat(2,1)<<" "<<t_mat(2,2)<<" "<<t_mat(2,3);
    qDebug()<<t_mat(3,0)<<" "<<t_mat(3,1)<<" "<<t_mat(3,2)<<" "<<t_mat(3,3);
}

int main(int argc, char **argv)
{
    //QT_ANDROID_VOLUME_KEYS
    QApplication app(argc, argv);


    ctRand::RandomReset();
    //QProcess tmp;
    //tmp.processEnvironment().insert(QString("QT_ANDROID_VOLUME_KEYS"), QString("true"));
//ctDelegat* tt;
    QResource::registerResource("res.rcc");
    //QSplashScreen m_scr(QPixmap(":/texture/GUI/loading.png"));
    //m_scr.show();
    //QResource::registerResource("muse.rcc");
    //QSurfaceFormat format;
    //format.setSamples(16);
    //format.setDepthBufferSize(24);
    //format.setStereo(true);
    //QMediaPlayer* player = new QMediaPlayer;
   // player->setMedia(QUrl::fromLocalFile("C:\\muse.mp3"));//(QUrl("assets:/muse.mp3"));
    //player->setVolume(50);
    //player->play();
    //QDesktopWidget *desk = QApplication::desktop();

    //qDebug()<<QApplication::desktop()->width()<<QApplication::desktop()->height();

    testAppWindow m_testWindow(&app);

    //m_testWindow.setFormat(format);
    //m_testWindow.SetResolution(1024, 768);
    //m_testWindow.resize(1024,500);
    qDebug()<<"default width: "<<m_testWindow.GetDefaultWidth()<<"default height: "<<m_testWindow.GetDefaultHeight();
    qDebug()<<"width: "<<m_testWindow.GetWidth()<<"height"<<m_testWindow.GetHeight();
    qDebug()<<"widthScale: "<<m_testWindow.GetWidthScale()<<"heightScale"<<m_testWindow.GetHeightScale();
    //m_testWindow.showMaximized();


    m_testWindow.showFullScreen();//showMaximized();
    //m_scr.hide();
    //m_scr.close();
    //delete m_scr;
    //m_testWindow.initialize();
    //m_splashScreen.hide();
    //m_splashScreen.close();

    //m_testWindow.show();


    //m_testWindow.setWindowState(Qt::WindowActive);//setWindowFlags(Qt::WindowStaysOnTopHint);
    //m_splashScreen.finish(&m_testWindow);
    //std::function<void(ccc*, int)> f_add_display = &ccc::ddd;
    //f_add_display(ee, 1);

    //d(1);
//    TriangleWindow window;
//    window.setFormat(format);
//    window.resize(640, 480);
//    window.show();

//    window.setAnimating(true);
    //m_splashScreen.finish(&m_testWindow);//close();//hide();
    //m_testWindow.renderNow11();
    return app.exec();
}


