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
    QOpenGLShaderProgram * m_lineShader;

    GLuint posAtribLoc;
    GLuint colorUniformLoc;
    GLuint matrixUniform;
    GLuint transformMatrixUniform;
    GLuint meshVBOlines;

    uint32_t* rectDotIndexes;

    void GettingLineAttributes();
    void GenerateVBOforRect();
    void DrawRectLines();
protected:
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
public:
    //ctClickablePlane();
    explicit ctClickablePlane(ctShaderManager *);
    ctClickablePlane(ctShaderManager *, ctScene *);
    ctClickablePlane(ctShaderManager *, ctScene *, QOpenGLContext *);
    ctClickablePlane(ctShaderManager *, ctScene *, QOpenGLContext *, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);

    virtual ~ctClickablePlane();

    void SetRect(const ctRect& t_rect);
    ctRect GetRect() const;
    ctRect GetTransformedRect();
    //--------------------------
    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual ctEntity* Clone();
    //--------------------------
};

#endif // CTCLICKABLEPLANE_H
