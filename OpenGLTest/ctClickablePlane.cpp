#include "ctClickablePlane.h"
#include "ctShaderManager.h"

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager) : ctPlane(t_shaderManager)
{
    SetRect(QRectF(0,0,0,0));
    m_drawRect = true;
}

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager, ctScene * t_scene) : ctPlane(t_shaderManager, t_scene)
{
    SetRect(QRectF(0,0,0,0));
    m_drawRect = true;
}

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext) : ctPlane(t_shaderManager, t_scene, t_OpenGLContext)
{
    SetRect(QRectF(0,0,0,0));
    m_drawRect = true;
}

ctClickablePlane::ctClickablePlane(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext, QVector3D t_AA, QVector3D t_BB, ctPlane::PlaneType t_type) : ctPlane(t_shaderManager, t_scene, t_OpenGLContext, t_AA, t_BB, t_type)
{
    SetRect(QRectF(QPointF(t_AA.x(), t_AA.y()), QPointF(t_BB.x(), t_BB.y())));
    m_drawRect = true;
}

ctClickablePlane::~ctClickablePlane()
{

}

void ctClickablePlane::SetRect(const QRectF &t_rect)
{
    m_rect = t_rect;
}

QRectF ctClickablePlane::GetRect() const
{
    return m_rect;
}

void ctClickablePlane::Update()
{
    ctPlane::Update();
}

void ctClickablePlane::Init()
{
    ctPlane::Init();

    m_lineShader = GetShaderManager()->GetShaderProgram("lineShader");
    GenerateVBOforRect();
    m_rectColor = QVector3D(0,1,0);
    //m_rectColor.x();
    //m_color = m_rectColor;
    //m_color.SetX(0);
    //m_color.SetY(1);
    //m_color.SetZ(0);
    //m_color.SetY(254);
    //m_color.SetZ(23);
    qDebug()<<"init ctPlane";
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
}

void ctClickablePlane::GenerateVBOforRect()
{
    //TODO: Need refine!
    float * completeBuffer = new float[12]; // positions count + texture coord count
    completeBuffer[0] = m_rect.topLeft().x();
    completeBuffer[1] = m_rect.topLeft().y();
    completeBuffer[2] = 1;
    completeBuffer[3] = m_rect.topRight().x();
    completeBuffer[4] = m_rect.topRight().y();
    completeBuffer[5] = 1;
    completeBuffer[6] = m_rect.bottomRight().x();
    completeBuffer[7] = m_rect.bottomRight().y();
    completeBuffer[8] = 1;
    completeBuffer[9] = m_rect.bottomLeft().x();
    completeBuffer[10] = m_rect.bottomLeft().y();
    completeBuffer[11] = 1;

    GetOpenGLContext()->functions()->glGenBuffers(1, &meshVBOlines);
    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, meshVBOlines);

    GetOpenGLContext()->functions()->glBufferData(GL_ARRAY_BUFFER, (12) * sizeof(GLfloat),
        completeBuffer, GL_STATIC_DRAW);
    delete[] completeBuffer;

    rectDotIndexes = new uint32_t[4];
    for(int i = 0; i < 4; ++i)
    {
        rectDotIndexes[i] = i;
    }
}

void ctClickablePlane::DrawRectLines()
{
    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, meshVBOlines);

    if (posAtribLoc != -1)
    {
        GetOpenGLContext()->functions()->glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE,
            (3 * sizeof(float)), (const GLvoid*)0);
        GetOpenGLContext()->functions()->glEnableVertexAttribArray(posAtribLoc);
    }
    else
    {qDebug()<<"isShit pos!!!";}

    /*qDebug()<<*/m_lineShader->bind();

    m_lineShader->setUniformValue(matrixUniform, GetProjectionMatrix().GetMatrix());
    //m_lineShader->setUniformValueArray();
    m_lineShader->setUniformValue(colorUniformLoc, m_rectColor);

    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, rectDotIndexes);


    GetOpenGLContext()->functions()->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_lineShader->release();
}
