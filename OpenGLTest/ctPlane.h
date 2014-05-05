#ifndef CTPLANE_H
#define CTPLANE_H

#include "ctObject.h"
#include <QVector3D>
#include <QMatrix4x4>
#include "shadermanager.h"
#include <QtGui/QOpenGLFunctions>
#include "ctTransform.h"
#include "ctTexture.h"

class ctPlane : public ctObject
{
public:
    enum PlaneType
    {
        Colored,
        Textured
    };
private:
    friend ctEntity* Clone();
    //ShaderManager * m_shaderManagerOld;
    QOpenGLShaderProgram * m_currentShader;
    QVector3D m_AA;
    QVector3D m_BB;
    PlaneType m_currentType;
    GLuint posAtribLoc;
    GLuint colorAtribLoc;
    GLuint textureLocation;
    GLuint matrixUniform;
    GLuint transformMatrixUniform;
    //GLuint textureIndex;
    GLuint meshVBO;
    QVector3D m_color;
    //float* planePositions;
    unsigned short* planeIndexes;
    //float* planeTextureCoords;
    //TODO: NEED REMOVE planeColor
    float* planeColor;
    ctTexture* m_texture;
    void GettingAttributes(QOpenGLShaderProgram * t_shaderProgram);
protected:
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
    virtual void ResizeMesh(QVector3D t_AA, QVector3D t_BB);
public:
    //ctPlane(){}
    //ctPlane(ShaderManager *t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    explicit ctPlane(ctShaderManager *){}
    ctPlane(ctShaderManager *, ctScene *){}
    ctPlane(ctShaderManager *, ctScene *, QOpenGLContext *){}
    ctPlane(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    virtual ~ctPlane();

    void InitShader();
    void InitShader(QOpenGLShaderProgram * t_initedShader);
    void InitShader(const char * t_shaderProgrammName);
    void InitShader(QString t_shaderProgrammName);
    void SetColor(QVector3D t_color);
    void SetTexture(const char * t_textureFileName, bool t_needResize = false);
    void SetTexture(QString t_textureFileName, bool t_needResize = false);
    void SetTexture(ctTexture* t_texture);
    void Draw(QMatrix4x4);
    //void DrawTexturedOld(QMatrix4x4);
    void DrawColored(QMatrix4x4);
    void DrawTextured(QMatrix4x4);
    void GenerateCompleteBuffer(QVector3D t_AA, QVector3D t_BB);
    //GLuint CreateTexture(const char *fileName, const char *fileFormat);

    //----Overload-functions----
    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual ctEntity* Clone();
    //--------------------------

};

#endif // CTPLANE_H
