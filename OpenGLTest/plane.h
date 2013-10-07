#ifndef PLANE_H
#define PLANE_H
#include <QVector3D>
#include <QMatrix4x4>
#include "shadermanager.h"
#include <QtGui/QOpenGLFunctions>
class Plane
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
    GLuint textureIndex;
    GLuint meshVBO;
    float* planePositions;
    uint32_t* planeIndexes;
    float* planeTextureCoords;
    float* planeColor;
    //float* planeCompleteBuffer;
    GLuint TextureCreateFromTGA(const char *fileName);
    void SetupPlaneCoords(QVector3D t_AA, QVector3D t_BB);
public:
    Plane(ShaderManager *t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    ~Plane();
    void InitShader();
    void SetColor(QVector3D t_color);
    void SetTexture(const char * t_textureFileName);
    void Draw(QMatrix4x4);
    void DrawTextured(QMatrix4x4);
    void DrawColored(QMatrix4x4);
    void GenerateCompleteBuffer();
    GLuint CreateTexture(const char *fileName, const char *fileFormat);
};

#endif // PLANE_H
