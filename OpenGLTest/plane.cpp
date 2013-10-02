#include "plane.h"
#include <QFile>

Plane::Plane(ShaderManager *t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type)
{
    meshVBO = 0;
    textureIndex = 0;
    m_currentType = t_type;
    m_AA = t_AA;
    m_BB = t_BB;
    m_shaderManager = t_shaderManager;
    SetupPlaneCoords(t_AA, t_BB);
    SetColor(QVector3D(1,255,1));
}

//Only For Texrtured Plane
void Plane::GenerateCompleteBuffer() // call only after shader init
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

    glGenBuffers(1, &meshVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);

    glBufferData(GL_ARRAY_BUFFER, (positionsOffset + texCoordOffset) * sizeof(GLfloat),
        completeBuffer, GL_STATIC_DRAW);

}

GLuint Plane::TextureCreateFromTGA(const char* fileName)
{
    TGAHeader *header;
    uint8_t   *buffer;
    uint32_t  size;
    GLint     format, internalFormat;
    GLuint    texture;

    QString fileNametmp(fileName);
    QFile * m_file = new QFile(fileNametmp);
    size = m_file->size();
    m_file->open(QFile::ReadOnly);
    m_file->seek(0);
    QByteArray tmp = m_file->readAll();
    buffer = new uint8_t[size];

    for(int i = 0; i< size; ++i)
    {
        buffer[i] = (uint8_t)tmp.data()[i];
    }
    if (size <= sizeof(TGAHeader))
    {
        qDebug()<<"Too small file '%s'\n";
            delete[] buffer;
            return 0;
    }

    header = (TGAHeader*)buffer;

    if (header->datatype != 2 || (header->bitperpel != 24 && header->bitperpel != 32))
    {
        qDebug()<<"Wrong TGA format '%s'\n";
            delete[] buffer;
            return 0;
    }

    format = (header->bitperpel == 24 ? GL_RGB : GL_RGBA);
    internalFormat = (format == GL_RGB ? GL_RGB : GL_RGBA);

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, header->width, header->height, 0, format,
            GL_UNSIGNED_BYTE, (const GLvoid*)(buffer + sizeof(TGAHeader) + header->idlength));

    delete[] buffer;

    return texture;
}

void Plane::SetTexture(const char* t_textureFileName)
{
    textureIndex = TextureCreateFromTGA(t_textureFileName);

    if (!textureIndex)
    {
        qDebug()<<"BadTextureIndex";
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
}

// TODO: Refine To QVector4D for using Alpha
void Plane::SetColor(QVector3D t_color)
{
    planeColor = new float[12];
    for(int i = 0; i < 4; ++i)
    {
        planeColor[0 + i] = t_color.x();
        planeColor[1 + i] = t_color.y();
        planeColor[2 + i] = t_color.z();
    }
}

void Plane::SetupPlaneCoords(QVector3D t_AA, QVector3D t_BB)
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

void Plane::Draw(QMatrix4x4 t_projectionMatrix)
{
    if(m_currentType == Colored)
    {
        DrawColored(t_projectionMatrix);
    }
    else if(m_currentType == Textured)
    {
        DrawTextured(t_projectionMatrix);
    }
}

void Plane::DrawColored(QMatrix4x4 t_projectionMatrix)
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

void Plane::DrawTextured(QMatrix4x4 t_projectionMatrix)
{
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

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, planeIndexes);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_currentShader->release();
}

void Plane::InitShader()
{
    if(m_currentType == Colored)
    {
        m_currentShader = m_shaderManager->SetUpShaderProgram(0, 0);
        posAtribLoc = m_currentShader->attributeLocation("posAttr");
        colorAtribLoc = m_currentShader->attributeLocation("colAttr");
        matrixUniform = m_currentShader->uniformLocation("matrix");
    }
    else if(m_currentType == Textured)
    {
        m_currentShader = m_shaderManager->SetUpShaderProgram(1, 1);
        posAtribLoc = m_currentShader->attributeLocation("position");
        colorAtribLoc = m_currentShader->attributeLocation("texcoord");
        matrixUniform = m_currentShader->uniformLocation("modelViewProjectionMatrix");
        textureLocation = m_currentShader->uniformLocation("colorTexture");
    }
}
