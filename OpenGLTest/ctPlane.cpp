#include "ctPlane.h"
#include <QFile>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QDebug>
#include "ctShaderManager.h"
ctPlane::ctPlane(ShaderManager *t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type)
{
    meshVBO = 0;
    textureIndex = 0;
    m_currentType = t_type;
    m_AA = t_AA;
    m_BB = t_BB;
    m_shaderManagerOld = t_shaderManager;
    SetupPlaneCoords(t_AA, t_BB);
    SetColor(QVector3D(1,255,1));
    //SetDefault(t_shaderManager,0,0);
    //m_transform = new ctTransform();
}

ctPlane::ctPlane(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type)
{
    SetDefault(t_shaderManager, t_scene, t_OpenGLContext);
    m_currentType = t_type;
    m_AA = t_AA;
    m_BB = t_BB;
    SetupPlaneCoords(t_AA, t_BB);
}

ctPlane::~ctPlane()
{
    //UNDONE: NEED COMPLETE DESTRUSTION
    qDebug()<<"ctPlane Destroyed\n";
}

void ctPlane::GenerateCompleteBuffer()
{
    const int positionsOffset = 12;
    const int texCoordOffset = 8;
    float * completeBuffer = new float[positionsOffset + texCoordOffset]; // positions count + texture coord count
    for(int i = 0; i < positionsOffset; ++i)
    {
        completeBuffer[i] = planePositions[i];
    }
    for(int i = 0; i < texCoordOffset; ++i)
    {
        completeBuffer[positionsOffset + i] = planeTextureCoords[i];
    }

    GetOpenGLContext()->functions()->glGenBuffers(1, &meshVBO);
    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    GetOpenGLContext()->functions()->glBufferData(GL_ARRAY_BUFFER, (positionsOffset + texCoordOffset) * sizeof(GLfloat),
        completeBuffer, GL_STATIC_DRAW);
    delete[] completeBuffer;

}

GLuint ctPlane::CreateTexture(const char *fileName, const char *fileFormat = 0)
{
    QString strFileName(fileName);
    //QString strFileFormat(fileFormat);
    QImage * image = new QImage(strFileName);//, fileFormat);

    uint8_t   *buffer;
    uint32_t  size;
    GLint     format, internalFormat;
    GLuint    texture;

    buffer = new uint8_t[image->byteCount()];


    format = GL_RGBA;//(header->bitperpel == 24 ? GL_RGB : GL_RGBA);
    internalFormat = format;//(format == GL_RGB ? GL_RGB : GL_RGBA);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image->width(), image->height(), 0, format,
            GL_UNSIGNED_BYTE, (const GLvoid*)(image->bits()));

    delete[] buffer;

    delete image;

    return texture;
}

void ctPlane::SetTexture(const char* t_textureFileName)
{
    textureIndex = CreateTexture(t_textureFileName);

    if (!textureIndex)
    {
        qDebug()<<"BadTextureIndex";
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
}

// TODO: Refine To QVector4D for using Alpha
void ctPlane::SetColor(QVector3D t_color)
{
    planeColor = new float[12];
    for(int i = 0; i < 4; ++i)
    {
        planeColor[0 + i] = t_color.x();
        planeColor[1 + i] = t_color.y();
        planeColor[2 + i] = t_color.z();
    }
}

void ctPlane::SetupPlaneCoords(QVector3D t_AA, QVector3D t_BB)
{
    //Setup Dots Pos
    planePositions = new float[12];

    planePositions[0] = t_AA.x();
    planePositions[1] = t_AA.y();
    planePositions[2] = t_AA.z();

    planePositions[3] = t_BB.x();
    planePositions[4] = t_AA.y();
    planePositions[5] = t_AA.z();

    planePositions[6] = t_BB.x();
    planePositions[7] = t_BB.y();
    planePositions[8] = t_BB.z();

    planePositions[9] = t_AA.x();
    planePositions[10] = t_BB.y();
    planePositions[11] = t_BB.z();

    //SetupIndexes
    planeIndexes = new uint32_t[6];

    planeIndexes[0] = 2;
    planeIndexes[1] = 1;
    planeIndexes[2] = 0;

    planeIndexes[3] = 3;
    planeIndexes[4] = 2;
    planeIndexes[5] = 0;


    planeTextureCoords = new float[8];
    planeTextureCoords[0] = 1;
    planeTextureCoords[1] = 1;
    planeTextureCoords[2] = 0;
    planeTextureCoords[3] = 1;
    planeTextureCoords[4] = 0;
    planeTextureCoords[5] = 0;
    planeTextureCoords[6] = 1;
    planeTextureCoords[7] = 0;
}

void ctPlane::Draw(QMatrix4x4 t_projectionMatrix)
{
    if(m_currentType == Colored)
    {
        DrawColored(t_projectionMatrix);
    }
    else if(m_currentType == Textured)
    {
        DrawTextured(t_projectionMatrix);//DrawTexturedOld(t_projectionMatrix);
    }
}

void ctPlane::DrawColored(QMatrix4x4 t_projectionMatrix)
{
    m_currentShader->bind();
    m_currentShader->setUniformValue(matrixUniform, t_projectionMatrix);
    glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, planePositions);
    glVertexAttribPointer(colorAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, planeColor);

    glEnableVertexAttribArray(posAtribLoc);
    glEnableVertexAttribArray(colorAtribLoc);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, planeIndexes);

    glDisableVertexAttribArray(colorAtribLoc);
    glDisableVertexAttribArray(posAtribLoc);

    m_currentShader->release();
}

void ctPlane::DrawTexturedOld(QMatrix4x4 t_projectionMatrix)
{
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    const int positionsOffset = 12 * sizeof(float);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    if (posAtribLoc != -1)
    {
        glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE,
            (3 * sizeof(float)), (const GLvoid*)0);
        glEnableVertexAttribArray(posAtribLoc);
    }
    else
    {qDebug()<<"isShit pos!!!";}
    if (colorAtribLoc != -1)
    {
        glVertexAttribPointer(colorAtribLoc, 2, GL_FLOAT, GL_FALSE,
                              (2 * sizeof(float)), (const GLvoid*)positionsOffset);
        glEnableVertexAttribArray(colorAtribLoc);
    }
    else
    {qDebug()<<"isShit color!!!";}

    m_currentShader->bind();
    m_currentShader->setUniformValue(textureLocation, 0);
    m_currentShader->setUniformValue(matrixUniform, t_projectionMatrix);
    m_currentShader->setUniformValue(transformMatrixUniform, m_transform->GetLocalTransformMatrix().GetMatrix());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, planeIndexes);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_currentShader->release();
}

void ctPlane::DrawTextured(QMatrix4x4 t_projectionMatrix)
{
    GetOpenGLContext()->functions()->glActiveTexture(GL_TEXTURE0);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    const int positionsOffset = 12 * sizeof(float);

    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    if (posAtribLoc != -1)
    {
        GetOpenGLContext()->functions()->glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE,
            (3 * sizeof(float)), (const GLvoid*)0);
        GetOpenGLContext()->functions()->glEnableVertexAttribArray(posAtribLoc);
    }
    else
    {qDebug()<<"isShit pos!!!";}
    if (colorAtribLoc != -1)
    {
        GetOpenGLContext()->functions()->glVertexAttribPointer(colorAtribLoc, 2, GL_FLOAT, GL_FALSE,
                              (2 * sizeof(float)), (const GLvoid*)positionsOffset);
        GetOpenGLContext()->functions()->glEnableVertexAttribArray(colorAtribLoc);
    }
    else
    {qDebug()<<"isShit color!!!";}

    m_currentShader->bind();
    m_currentShader->setUniformValue(textureLocation, 0);
    m_currentShader->setUniformValue(matrixUniform, t_projectionMatrix);
    m_currentShader->setUniformValue(transformMatrixUniform, m_transform->GetLocalTransformMatrix().GetMatrix());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, planeIndexes);

    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_currentShader->release();
}

void ctPlane::InitShader()
{
//    if(r==0)
//    {
//        if(m_currentType == Colored)
//        {
//            m_currentShader = m_shaderManagerOld->SetUpShaderProgram(0, 0);
//        }
//        else if(m_currentType == Textured)
//        {
//            m_currentShader = m_shaderManagerOld->SetUpShaderProgram(2, 1);
//        }
//        GettingAnttibutes(m_currentShader);
//    }
//    else
//    {
    m_currentShader = m_shaderManager->SetUpShaderProgram("texturedModelVertexShaderSource", "texturedFragmentShaderSource", "texturedPlaneShader");// need replace this part to outside
    GettingAnttibutes(m_currentShader);
//    }
}

void ctPlane::InitShader(const char *t_shaderProgrammName)
{
    m_currentShader = m_shaderManager->GetShaderProgram(t_shaderProgrammName);
    GettingAnttibutes(m_currentShader);
}
void ctPlane::InitShader(QString t_shaderProgrammName)
{
    m_currentShader = m_shaderManager->GetShaderProgram(t_shaderProgrammName);
    GettingAnttibutes(m_currentShader);
}
void ctPlane::InitShader(QOpenGLShaderProgram *t_initedShader)
{
    m_currentShader = t_initedShader;
    GettingAnttibutes(m_currentShader);
}

void ctPlane::GettingAnttibutes(QOpenGLShaderProgram * t_shaderProgram)
{
//    if(m_currentType == Colored)
//    {
//        posAtribLoc = t_shaderProgram->attributeLocation("posAttr");
//        colorAtribLoc = t_shaderProgram->attributeLocation("colAttr");
//        matrixUniform = t_shaderProgram->uniformLocation("matrix");
//    }
//    else if(m_currentType == Textured)
//    {
    if(!t_shaderProgram)
    {qDebug()<<"Shit Shader Program";}
        posAtribLoc = t_shaderProgram->attributeLocation("position");
        colorAtribLoc = t_shaderProgram->attributeLocation("texcoord");
        matrixUniform = t_shaderProgram->uniformLocation("viewProjectionMatrix");
        transformMatrixUniform = t_shaderProgram->uniformLocation("modelMatrix");
        textureLocation = t_shaderProgram->uniformLocation("colorTexture");
//    }
}

void ctPlane::Init()
{
    InitShader();
    GenerateCompleteBuffer();
    m_isInitialized = true;
    //StartUpInit
}

void ctPlane::Draw()
{
    Draw(m_projectionMatrix.GetMatrix());
    //SelfDrawing
}

void ctPlane::Update()
{
    //Update Some States
}

void ctPlane::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContex)
{
    ctObject::SetDefault(t_shaderManager, t_scene, t_OpenGLContex);
    meshVBO = 0;
    textureIndex = 0;
}
