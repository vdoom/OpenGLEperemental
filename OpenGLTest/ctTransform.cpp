#include "ctTransform.h"
#include "ctEntity.h"
#include "QDebug"

ctTransform::ctTransform()
{
    SetDefault();
}

ctTransform::ctTransform(ctEntity * t_entity)
{
    SetDefault();
    m_entity = t_entity;
}

ctTransform::~ctTransform()
{}

void ctTransform::SetDefault()
{
    m_parent = 0;
    m_childrens = new QVector<ctTransform * >();
}

void ctTransform::Move(QVector3D t_pos)
{
    m_localTransform.Translate(t_pos);
}

void ctTransform::Scale(QVector3D t_scl)
{
    m_localTransform.Scale(t_scl);
}

void ctTransform::RotateByX(float t_angle)
{
    m_localTransform.RotateX(t_angle);
}

void ctTransform::RotateByY(float t_angle)
{
    m_localTransform.RotateY(t_angle);
}

void ctTransform::RotateByZ(float t_angle)
{
    m_localTransform.RotateZ(t_angle);
}

ctMatrix4 ctTransform::GetLocalTransformMatrix() const
{
    return m_localTransform;
}

ctMatrix4 ctTransform::GetGlobalTransformMatrix() const
{
    //return m_localTransform;
    if(!m_parent)
    {return GetLocalTransformMatrix();}
    else
    {
        ctMatrix4 tmpMat(m_parent->GetGlobalTransformMatrix());
        ctMatrix4 tmpMat1(m_localTransform);
        //tmpMat = m_localTransform.Multiply(tmpMat);
        return tmpMat1 * tmpMat;
    }
}

ctMatrix4 operator * (ctMatrix4 & t_mat1, ctMatrix4 & t_mat2)
{
    ctMatrix4 tmp(t_mat1);
    tmp.Multiply(t_mat2);
    return tmp;
}

ctEntity * ctTransform::GetEntity() const
{
    return m_entity;
}
//TODO: NEED TEST !!!
bool ctTransform::GetParentsVisibility() const
{
    if(!m_parent)
    {
        return m_entity->IsVisible();
    }
    else
    {
        ctTransform * parent = m_parent;
        while(parent)
        {
            parent = parent->GetParent();
            if(!parent->GetEntity()->IsVisible())
            {return false;}
            if(!parent->GetParent()) return parent->GetEntity()->IsVisible();
        }
        parent->GetEntity()->IsVisible();
    }
}

ctTransform * ctTransform::GetParent() const
{
    return m_parent;
}

bool ctTransform::IsVisible() const
{
    if(!m_entity) return false;
    return m_entity->IsVisible();
}

void ctTransform::SetVisible(bool t_visible)
{
    if(!m_entity) return;
    if(t_visible) m_entity->Show();
    else m_entity->Hide();
}

void ctTransform::SetLocalMatrix(const ctMatrix4 & t_matrix)
{
    m_localTransform = t_matrix;
}

void ctTransform::SetLocalMatrix(const QMatrix4x4 & t_matrix)
{
    m_localTransform.SetMatrix(t_matrix);
}

void ctTransform::SetParent(const ctTransform * t_parent)
{
    m_parent = const_cast<ctTransform*>(t_parent);
}
