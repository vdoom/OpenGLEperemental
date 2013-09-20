#include "shadermanager.h"

ShaderManager::ShaderManager()
{
    m_shaderProgram = new QOpenGLShaderProgram();
}

int ShaderManager::GetCountFragmentShaders()
{
    return m_fragmentShaders.count();
}

int ShaderManager::GetCountVertexShaders()
{
    return m_vertexShaders.count();
}

void ShaderManager::AddFragmentShader(const char *t_fragmentTxt)
{
    m_fragmentShaders.push_back(new QOpenGLShader(QOpenGLShader::Fragment, 0));
    m_fragmentShaders.last()->compileSourceCode(t_fragmentTxt);
}

void ShaderManager::AddVertexShader(const char *t_vertexTxt)
{
    m_vertexShaders.push_back(new QOpenGLShader(QOpenGLShader::Vertex));
    m_vertexShaders.last()->compileSourceCode(t_vertexTxt);
}

void ShaderManager::SetActiveFragmentShader(int t_fragmentShaderIndex)
{
    m_shaderProgram->addShader(m_fragmentShaders[t_fragmentShaderIndex]);
}

void ShaderManager::SetActiveVertexShader(int t_vertexShaderIndex)
{
    m_shaderProgram->addShader(m_vertexShaders[t_vertexShaderIndex]);
}

QOpenGLShaderProgram* ShaderManager::SetUpShaderProgram(int t_vertexShaderIndex, int t_fragmentShaderIndex)
{
    QOpenGLShaderProgram * tmpProgram = new QOpenGLShaderProgram();
    tmpProgram->addShader(m_vertexShaders[t_vertexShaderIndex]);
    tmpProgram->addShader(m_fragmentShaders[t_fragmentShaderIndex]);
    tmpProgram->link();
    m_shaderPrograms.push_back(tmpProgram);
//    m_shaderProgram->removeAllShaders();
//    SetActiveVertexShader(t_vertexShaderIndex);
//    SetActiveFragmentShader(t_fragmentShaderIndex);
//    m_shaderProgram->link();
    return tmpProgram;
}

QOpenGLShaderProgram* ShaderManager::GetCurrentShaderProgram()
{
    return m_shaderPrograms.last();
}

QOpenGLShaderProgram* ShaderManager::GetShaderProgram(int t_index)
{
    return m_shaderPrograms[t_index];
}
