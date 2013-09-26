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
    allBuffer = new GLfloat[12];
    allBuffer[0] = coordsArray[0];
    allBuffer[1] = coordsArray[1];
    allBuffer[2] = coordsArray[2];
    allBuffer[3] = coordsArray[3];
    allBuffer[4] = coordsArray[4];
    allBuffer[5] = coordsArray[5];
    allBuffer[6] = colorsArray[0];
    allBuffer[7] = colorsArray[1];
    allBuffer[8] = colorsArray[2];
    allBuffer[9] = colorsArray[3];
    allBuffer[10] = colorsArray[4];
    allBuffer[11] = colorsArray[5];
//    for(int i = 1; i<3 ++i)
//    {
//        for(int j = 0; i<3; ++i)
//        {
//            allBuffer[]
//        }
//    }
}

void Axis::InitShaders()
{static const int VERTEX_COLOR_OFFSET    = 6 * sizeof(GLfloat);
    m_currentShaderProgram = m_shaderManager->SetUpShaderProgram(0, 0);

    posAtribLoc = m_currentShaderProgram->attributeLocation("posAttr");
    colorAtribLoc = m_currentShaderProgram->attributeLocation("colAttr");
    matrixUniform = m_currentShaderProgram->uniformLocation("matrix");

    // создадим и используем Vertex Array Object (VAO)
    //glGenVertexArrays(1, &meshVAO);
   // glBindVertexArray(meshVAO);

    // создадим и используем Vertex Buffer Object (VBO)
    glGenBuffers(1, &meshVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    // заполним VBO данными треугольника
    glBufferData(GL_ARRAY_BUFFER, 2 * (6 * sizeof(GLfloat)),
        allBuffer, GL_STATIC_DRAW);

    //positionLocation = glGetAttribLocation(shaderProgram, "position");
    if (posAtribLoc != -1)
    {
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE,
            (3 * sizeof(float)), (const GLvoid*)0);
        // разрешим использование атрибута
        glEnableVertexAttribArray(posAtribLoc);
    }
    else
    {qDebug()<<"isShit pos!!!";}
//    //glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
////------------------------------------------------------
//    glGenBuffers(1, &colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//    // заполним VBO данными треугольника
//    glBufferData(GL_ARRAY_BUFFER, 2 * (3 * sizeof(float)),
//        coordsArray, GL_STATIC_DRAW);
//    // получим позицию атрибута 'color' из шейдера
//    //colorLocation = glGetAttribLocation(shaderProgram, "colAttr");
    if (colorAtribLoc != -1)
    {
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(colorAtribLoc, 3, GL_FLOAT, GL_FALSE,
                              (3 * sizeof(float)), (const GLvoid*)VERTEX_COLOR_OFFSET);
        // разрешим использование атрибута
        glEnableVertexAttribArray(colorAtribLoc);
    }
    else
    {qDebug()<<"isShit color!!!";}
    //glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Axis::Draw(QMatrix4x4 t_projectionMatrix)
{

    static const int VERTEX_COLOR_OFFSET    = 6 * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    //positionLocation = glGetAttribLocation(shaderProgram, "position");
    if (posAtribLoc != -1)
    {
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE,
            (3 * sizeof(float)), (const GLvoid*)0);
        // разрешим использование атрибута
        glEnableVertexAttribArray(posAtribLoc);
    }
    else
    {qDebug()<<"isShit pos!!!";}
//    //glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
////------------------------------------------------------
//    glGenBuffers(1, &colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//    // заполним VBO данными треугольника
//    glBufferData(GL_ARRAY_BUFFER, 2 * (3 * sizeof(float)),
//        coordsArray, GL_STATIC_DRAW);
//    // получим позицию атрибута 'color' из шейдера
//    //colorLocation = glGetAttribLocation(shaderProgram, "colAttr");
    if (colorAtribLoc != -1)
    {
        // назначим на атрибут параметры доступа к VBO
        glVertexAttribPointer(colorAtribLoc, 3, GL_FLOAT, GL_FALSE,
                              (3 * sizeof(float)), (const GLvoid*)VERTEX_COLOR_OFFSET);
        // разрешим использование атрибута
        glEnableVertexAttribArray(colorAtribLoc);
    }
    else
    {qDebug()<<"isShit color!!!";}
    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_currentShaderProgram->bind();
    m_currentShaderProgram->setUniformValue(matrixUniform, t_projectionMatrix);
    //glBindVertexArray(meshVBO);
   // glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, coordsArray);
    //glVertexAttribPointer(colorAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, colorsArray);

    //glEnableVertexAttribArray(posAtribLoc);
    //glEnableVertexAttribArray(colorAtribLoc);


//    glDrawArrays(GL_LINES, 0, 2);
//    glBindVertexArray(colorVBO);
    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
    //glDisableVertexAttribArray(colorAtribLoc);
    //glDisableVertexAttribArray(posAtribLoc);

    m_currentShaderProgram->release();
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
