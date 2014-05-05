#ifndef CTCLICKABLEPLANE_H
#define CTCLICKABLEPLANE_H

#include "ctPlane.h"
#include "ctRect.h"
#include "test.h"

class ctClickablePlane : public ctPlane
{
private:
    ctRect m_rect;
    QVector3D m_rectColor;
    ctVector3Df m_color;
    bool m_drawRect;
    QGLShaderProgram * m_lineShader;

    GLuint posAtribLoc;
    GLuint colorUniformLoc;
    GLuint matrixUniform;
    GLuint transformMatrixUniform;
    GLuint meshVBOlines;

    GLshort* rectDotIndexes;

    void GettingLineAttributes();
    void GenerateVBOforRect();
    void DrawRectLines();
    virtual void ResizeMesh(QVector3D t_AA, QVector3D t_BB);
protected:
    virtual void SetDefault(ctShaderManager *, ctScene *, QGLContext *);
public:
    //ctClickablePlane();
    explicit ctClickablePlane(ctShaderManager *);
    ctClickablePlane(ctShaderManager *, ctScene *);
    ctClickablePlane(ctShaderManager *, ctScene *, QGLContext *);
    ctClickablePlane(ctShaderManager *, ctScene *, QGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);

    virtual ~ctClickablePlane();

    void SetRect(const ctRect& t_rect);
    ctRect GetRect() const;
    ctRect GetTransformedRect();

    bool IsIntersect(QVector3D);
    //--------------------------
    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual ctEntity* Clone();
    //--------------------------
};

#endif // CTCLICKABLEPLANE_H
