#include "ctClickablePlane.h"

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

void ctClickablePlane::DrawRectLines()
{
}
