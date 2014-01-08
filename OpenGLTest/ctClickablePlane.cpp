#include "ctClickablePlane.h"
#include "ctShaderManager.h"

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager) : ctPlane(t_shaderManager), meshVBOlines(0), rectDotIndexes(0)
{
    SetRect(ctRect());
    m_drawRect = true;
}

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager, ctScene * t_scene) : ctPlane(t_shaderManager, t_scene), meshVBOlines(0), rectDotIndexes(0)
{
    SetRect(ctRect());
    m_drawRect = true;
}

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext) : ctPlane(t_shaderManager, t_scene, t_OpenGLContext), meshVBOlines(0), rectDotIndexes(0)
{
    SetRect(ctRect());
    m_drawRect = true;
}

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext, QVector3D t_AA, QVector3D t_BB, ctPlane::PlaneType t_type) : ctPlane(t_shaderManager, t_scene, t_OpenGLContext, t_AA, t_BB, t_type), meshVBOlines(0), rectDotIndexes(0)
{
    SetRect(ctRect(QVector3D(t_BB.x(), t_AA.y(), 1), QVector3D(t_AA.x(), t_AA.x(), 1), QVector3D(t_BB.x(), t_BB.y(), 1), QVector3D(t_AA.x(), t_BB.y(), 1)));
    m_drawRect = true;
}

ctClickablePlane::~ctClickablePlane()
{
    GetOpenGLContext()->functions()->glDeleteBuffers(1, &meshVBOlines);
}

void ctClickablePlane::SetRect(const ctRect &t_rect)
{
    m_rect = t_rect;
}

ctRect ctClickablePlane::GetRect() const
{return m_rect;}

ctRect ctClickablePlane::GetTransformedRect()
{return GetTransform()->GetGlobalTransformMatrix() * m_rect;}

void ctClickablePlane::Update()
{
    ctPlane::Update();
    //GetTransform()->Move(QVector3D(0.5f,0,0));

    static int ttt = 0;
    if(!ttt)
    {ttt = 1;
        GenerateVBOforRect();
    }
}

void ctClickablePlane::Init()
{
    ctPlane::Init();

    m_lineShader = GetShaderManager()->GetShaderProgram("lineShader");
    m_rectColor = QVector3D(1,1,0);

    GettingLineAttributes();
}

void ctClickablePlane::Draw()
{
    if(m_drawRect)
        DrawRectLines();

    ctPlane::Draw();
}

void ctClickablePlane::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    ctPlane::SetDefault(t_shaderManager, t_scene, t_OpenGLContext);
}

ctEntity* ctClickablePlane::Clone()
{
    return (ctEntity*)this;
}

void ctClickablePlane::GettingLineAttributes()
{
    if(!m_lineShader)
    {qDebug()<<"Shit Shader Program";}

    posAtribLoc   = m_lineShader->attributeLocation("posAttr");
    colorUniformLoc = m_lineShader->uniformLocation("col");
    matrixUniform = m_lineShader->uniformLocation("matrix");
    transformMatrixUniform = m_lineShader->uniformLocation("modelMatrix");
    qDebug()<<"Getting Attribs";
}

void ctClickablePlane::GenerateVBOforRect()
{
    if(meshVBOlines)
    {
        GetOpenGLContext()->functions()->glDeleteBuffers(1, &meshVBOlines);
    }
    ctRect m_drawingRect;
    m_drawingRect = GetTransform()->GetGlobalTransformMatrix() * m_rect;

    GLfloat * completeBuffer = new GLfloat[12];
    completeBuffer[0] = m_drawingRect.GetTopLeft().x();
    completeBuffer[1] = m_drawingRect.GetTopLeft().y();
    completeBuffer[2] = m_drawingRect.GetTopLeft().z();
    completeBuffer[3] = m_drawingRect.GetTopRight().x();
    completeBuffer[4] = m_drawingRect.GetTopRight().y();
    completeBuffer[5] = m_drawingRect.GetTopRight().z();
    completeBuffer[6] = m_drawingRect.GetBottomRight().x();
    completeBuffer[7] = m_drawingRect.GetBottomRight().y();
    completeBuffer[8] = m_drawingRect.GetBottomRight().z();
    completeBuffer[9] = m_drawingRect.GetBottomLeft().x();
    completeBuffer[10] = m_drawingRect.GetBottomLeft().y();
    completeBuffer[11] = m_drawingRect.GetBottomLeft().z();

//    qDebug()<<"CompleteBuffer ->";
//    for(int i = 0; i < 12; ++i)
//    {
//        qDebug()<<completeBuffer[i];
//    }
//    qDebug()<<"<-";

    GetOpenGLContext()->functions()->glGenBuffers(1, &meshVBOlines);
    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, meshVBOlines);

    GetOpenGLContext()->functions()->glBufferData(GL_ARRAY_BUFFER, (12) * sizeof(GLfloat),
        completeBuffer, GL_STATIC_DRAW);
    delete[] completeBuffer;

    if(rectDotIndexes) delete[] rectDotIndexes;

    rectDotIndexes = new GLshort[4];
    for(int i = 0; i < 4; ++i)
    {
        rectDotIndexes[i] = i;
    }
}

void ctClickablePlane::DrawRectLines()
{
    //glDisable(GL_DEPTH_TEST);
    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, meshVBOlines);

    if (posAtribLoc != -1)
    {
        GetOpenGLContext()->functions()->glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE,
            (3 * sizeof(GLfloat)), (const GLvoid*)0);
        GetOpenGLContext()->functions()->glEnableVertexAttribArray(posAtribLoc);
    }
    else
    {qDebug()<<"isShit pos!!!";}

    m_lineShader->bind();

    m_lineShader->setUniformValue(matrixUniform, GetProjectionMatrix().GetMatrix());
    m_lineShader->setUniformValue(colorUniformLoc, m_rectColor);
    m_lineShader->setUniformValue(transformMatrixUniform, GetTransform()->GetGlobalTransformMatrix().GetMatrix());

    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, rectDotIndexes);


    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_lineShader->release();
    //glEnable(GL_DEPTH_TEST);
}
