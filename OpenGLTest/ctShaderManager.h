#ifndef CTSHADERMANAGER_H
#define CTSHADERMANAGER_H

#include <QObject>
#include <QtCore/qmath.h>
#include <QtGui/QOpenGLFunctions>
//#include <QtGui/QOpenGLShaderProgram>
#include <QGLShaderProgram>
#include <QOpenGLContext>
//#include <QVector>
#include <qhash.h>
//TODO: Perhapse need to be a singleton
class ctShaderManager
{
private:
    QHash<QString, QGLShader*> m_vertexShaders;
    QHash<QString, QGLShader*> m_fragmentShaders;
    QHash<QString, QGLShaderProgram*> m_shaderPrograms;
    QGLContext * m_OpenGLContext;
public:
    ctShaderManager();
    ctShaderManager(QGLContext * t_OpenGLContext);
    ~ctShaderManager();
    int AddVertexShader(const char * t_shaderTxt, const char * t_name);
    int AddVertexShader(QString t_shaderTxt, QString t_name);
    int AddFragmentShader(const char * t_shaderTxt, const char * t_name);
    int AddFragmentShader(QString t_shaderTxt, QString t_name);
    QGLShaderProgram* SetUpShaderProgram(const char * t_vertexShaderName, const char * t_fragmentShaderName, const char * t_name);//(int t_vertexShaderIndex, int t_fragmentShaderIndex);
    QGLShaderProgram* SetUpShaderProgram(QString t_vertexShaderName, QString t_fragmentShaderName, QString t_name);
    //QOpenGLShaderProgram* GetCurrentShaderProgram();
    QGLShaderProgram* GetShaderProgram(const char * t_name);//(int t_index);
    QGLShaderProgram* GetShaderProgram(QString t_name);
};

#endif // CTSHADERMANAGER_H
