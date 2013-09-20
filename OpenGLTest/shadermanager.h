#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <QObject>
#include <QtCore/qmath.h>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QVector>

class ShaderManager
{
private:
    QVector<QOpenGLShader*> m_vertexShaders;
    QVector<QOpenGLShader*> m_fragmentShaders;
    QVector<QOpenGLShaderProgram*> m_shaderPrograms;
    QOpenGLShaderProgram* m_shaderProgram;
public:
    ShaderManager();
    ~ShaderManager();
    void AddVertexShader(const char * t_shaderTxt);
    void AddFragmentShader(const char * t_segmentTxt);
    int GetCountVertexShaders();
    int GetCountFragmentShaders();
    void SetActiveVertexShader(int t_vertexShaderIndex);
    void SetActiveFragmentShader(int t_fragmentShaderIndex);
    QOpenGLShaderProgram* SetUpShaderProgram(int t_vertexShaderIndex, int t_fragmentShaderIndex);
    QOpenGLShaderProgram* GetCurrentShaderProgram();
    QOpenGLShaderProgram* GetShaderProgram(int t_index);
};

#endif // SHADERMANAGER_H
