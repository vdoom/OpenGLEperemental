#ifndef CTPLANE_H
#define CTPLANE_H

#include "ctObject.h"
#include <QVector3D>
#include <QMatrix4x4>
#include "shadermanager.h"
#include <QtGui/QOpenGLFunctions>
#include "ctTransform.h"

class ctPlane : public ctObject
{
public:
    enum PlaneType
    {
        Colored,
        Textured
    };
private:
    struct TGAHeader
    {
            uint8_t  idlength;
            uint8_t  colormap;
            uint8_t  datatype;
            uint8_t  colormapinfo[5];
            uint16_t xorigin;
            uint16_t yorigin;
            uint16_t width;
            uint16_t height;
            uint8_t  bitperpel;
            uint8_t  description;
    };
    ShaderManager * m_shaderManager;
    QOpenGLShaderProgram * m_currentShader;
    QVector3D m_AA;
    QVector3D m_BB;
    PlaneType m_currentType;
    GLuint posAtribLoc;
    GLuint colorAtribLoc;
    GLuint textureLocation;
    GLuint matrixUniform;
    GLuint transformMatrixUniform;
    GLuint textureIndex;
    GLuint meshVBO;
    float* planePositions;
    uint32_t* planeIndexes;
    float* planeTextureCoords;
    float* planeColor;
    //float* planeCompleteBuffer;
    GLuint TextureCreateFromTGA(const char *fileName);
    void SetupPlaneCoords(QVector3D t_AA, QVector3D t_BB);
    //();
    //-------------------------------------------------------
    //ctTransform m_transform;
//    ctTransform * m_transform;
//    ctMatrix4 m_projectionMatrix;
    //-------------------------------------------------------

public:
    //ctPlane(){}
    ctPlane(ShaderManager *t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    ~ctPlane();

    void InitShader();
    void SetColor(QVector3D t_color);
    void SetTexture(const char * t_textureFileName);
    void Draw(QMatrix4x4);
    void DrawTextured(QMatrix4x4);
    void DrawColored(QMatrix4x4);
    void GenerateCompleteBuffer();
    GLuint CreateTexture(const char *fileName, const char *fileFormat);

    //----Overload-functions----
    virtual void Update();
    virtual void Draw();
    virtual void Init();
    //--------------------------
//    ctTransform * GetTransform();// const;
//    ctMatrix4 GetProjectionMatrix();// const;
//    void SetProjectionMatrix(ctMatrix4 & t_projMat);
//    void SetProjectionMatrix(QMatrix4x4 & t_projMat);
};

#endif // CTPLANE_H
