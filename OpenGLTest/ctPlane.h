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
    ShaderManager * m_shaderManagerOld;
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
    void SetupPlaneCoords(QVector3D t_AA, QVector3D t_BB);
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
    void GettingAnttibutes(QOpenGLShaderProgram * t_shaderProgram);
public:
    //ctPlane(){}
    ctPlane(ShaderManager *t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    explicit ctPlane(ctShaderManager *){}
    ctPlane(ctShaderManager *, ctScene *){}
    ctPlane(ctShaderManager *, ctScene *, QOpenGLContext *){}
    ctPlane(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    ~ctPlane();

    void InitShader();
    void InitShader(QOpenGLShaderProgram * t_initedShader);
    void InitShader(const char * t_shaderProgrammName);
    void InitShader(QString t_shaderProgrammName);
    void SetColor(QVector3D t_color);
    void SetTexture(const char * t_textureFileName);
    void Draw(QMatrix4x4);
    void DrawTextured(QMatrix4x4);
    void DrawColored(QMatrix4x4);
    void DrawTexturedNew(QMatrix4x4);
    void GenerateCompleteBuffer();
    GLuint CreateTexture(const char *fileName, const char *fileFormat);

    //----Overload-functions----
    virtual void Update();
    virtual void Draw();
    virtual void Init();
    //--------------------------

};

#endif // CTPLANE_H
