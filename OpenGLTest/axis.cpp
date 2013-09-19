#include "axis.h"
#include <QDebug>

Axis::Axis(QVector3D t_axisVector, QVector3D t_axisColor, ShaderManager * t_shaderManager)
{
    m_axisVector = t_axisVector;
    m_axisColor = t_axisColor;
    m_shaderManager = t_shaderManager;
    m_matrix.setToIdentity();
    SetUpCoords(m_axisVector);
    SetUpColor(m_axisColor);
}

void Axis::Draw(QMatrix4x4 t_projectionMatrix)
{
    m_shaderManager->SetUpShaderProgram(0, 0);
    posAtribLoc = m_shaderManager->GetCurrentShaderProgram()->attributeLocation("posAttr");
    colorAtribLoc = m_shaderManager->GetCurrentShaderProgram()->attributeLocation("colAttr");
    matrixUniform = m_shaderManager->GetCurrentShaderProgram()->uniformLocation("matrix");
    m_shaderManager->GetCurrentShaderProgram()->bind();
    m_shaderManager->GetCurrentShaderProgram()->setUniformValue(matrixUniform, t_projectionMatrix);
    glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, coordsArray);
    glVertexAttribPointer(colorAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, colorsArray);

    glEnableVertexAttribArray(posAtribLoc);
    glEnableVertexAttribArray(colorAtribLoc);

    glDrawArrays(GL_LINES, 0, 2);

    glDisableVertexAttribArray(colorAtribLoc);
    glDisableVertexAttribArray(posAtribLoc);

    m_shaderManager->GetCurrentShaderProgram()->release();
}

void Axis::SetUpCoords(QVector3D t_axisVector)
{
    coordsArray = new GLfloat[6];
    coordsArray[0] = t_axisVector.x();
    coordsArray[1] = t_axisVector.y();
    coordsArray[2] = t_axisVector.z();
    coordsArray[3] = 0.0f;
    coordsArray[4] = 0.0f;
    coordsArray[5] = 0.0f;
}

void Axis::SetUpColor(QVector3D t_axisColor)
{
    colorsArray = new GLfloat[6];
    colorsArray[0] = t_axisColor.x();
    colorsArray[1] = t_axisColor.y();
    colorsArray[2] = t_axisColor.z();
    colorsArray[3] = t_axisColor.x();
    colorsArray[4] = t_axisColor.y();
    colorsArray[5] = t_axisColor.z();
}
