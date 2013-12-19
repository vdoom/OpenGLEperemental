#include "ctRect.h"
#include "QDebug"

ctRect::ctRect()
{
    SetUpRect(QVector3D(0,0,0), QVector3D(0,0,0), QVector3D(0,0,0), QVector3D(0,0,0));
}

ctRect::ctRect(QVector3D t_topLeft, QVector3D t_topRight, QVector3D t_bottomLeft, QVector3D t_bottomRight)
{
    SetUpRect(t_topLeft, t_topRight, t_bottomLeft, t_bottomRight);
}

ctRect::~ctRect(){}

void ctRect::SetBottomLeft(const QVector3D &t_bottomLeft)
{
    m_bottomLeft = t_bottomLeft;
}

void ctRect::SetBottomRight(const QVector3D &t_bottomRight)
{
    m_bottomRight = t_bottomRight;
}

void ctRect::SetTopLeft(const QVector3D &t_topLeft)
{
    m_topLeft = t_topLeft;
}

void ctRect::SetTopRight(const QVector3D &t_topRight)
{
    m_topRigth = t_topRight;
}

void ctRect::SetUpRect(QVector3D t_topLeft, QVector3D t_topRight, QVector3D t_bottomLeft, QVector3D t_bottomRight)
{
    SetBottomLeft(t_bottomLeft);
    SetBottomRight(t_bottomRight);
    SetTopLeft(t_topLeft);
    SetTopRight(t_topRight);
}

QVector3D ctRect::GetBottomLeft() const
{
    return m_bottomLeft;
}

QVector3D ctRect::GetBottomRight() const
{
    return m_bottomRight;
}

QVector3D ctRect::GetTopLeft() const
{
    return m_topLeft;
}

QVector3D ctRect::GetTopRight() const
{
    return m_topRigth;
}

ctRect operator * (const ctMatrix4& t_mat, const ctRect& t_rect)
{
    return ctRect((t_mat.GetMatrix() * t_rect.GetTopLeft()), (t_mat.GetMatrix() * t_rect.GetTopRight()), (t_mat.GetMatrix() * t_rect.GetBottomLeft()), (t_mat.GetMatrix() * t_rect.GetBottomRight()));
}

ctRect operator * (const QMatrix4x4& t_mat, const ctRect& t_rect)
{
    return ctRect((t_mat * t_rect.GetTopLeft()), (t_mat * t_rect.GetTopRight()), (t_mat * t_rect.GetBottomLeft()), (t_mat * t_rect.GetBottomRight()));
}

