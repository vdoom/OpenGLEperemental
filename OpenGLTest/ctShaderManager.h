#ifndef CTSHADERMANAGER_H
#define CTSHADERMANAGER_H

#include <QObject>
#include <QtCore/qmath.h>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QOpenGLContext>
//#include <QVector>
#include <qhash.h>

class ctShaderManager
{
private:
    QHash<QString, QOpenGLShader*> m_vertexShaders;
    QHash<QString, QOpenGLShader*> m_fragmentShaders;
    QHash<QString, QOpenGLShaderProgram*> m_shaderPrograms;
    QOpenGLContext * m_OpenGLContext;
public:
    ctShaderManager();
    ctShaderManager(QOpenGLContext * t_OpenGLContext);
    ~ctShaderManager();
    int AddVertexShader(const char * t_shaderTxt, const char * t_name);
    int AddVertexShader(QString t_shaderTxt, QString t_name);
    int AddFragmentShader(const char * t_shaderTxt, const char * t_name);
    int AddFragmentShader(QString t_shaderTxt, QString t_name);
    QOpenGLShaderProgram* SetUpShaderProgram(const char * t_vertexShaderName, const char * t_fragmentShaderName, const char * t_name);//(int t_vertexShaderIndex, int t_fragmentShaderIndex);
    QOpenGLShaderProgram* SetUpShaderProgram(QString t_vertexShaderName, QString t_fragmentShaderName, QString t_name);
    //QOpenGLShaderProgram* GetCurrentShaderProgram();
    QOpenGLShaderProgram* GetShaderProgram(const char * t_name);//(int t_index);
    QOpenGLShaderProgram* GetShaderProgram(QString t_name);
};

#endif // CTSHADERMANAGER_H
