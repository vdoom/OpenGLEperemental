#include "ctTransform.h"

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
    //m_uuid = QUuid::createUuid();
    //m_name = QString("transform");
    //m_localTransform.();
    m_parent = 0;
    m_childrens = new QVector<ctTransform * >();
}

void ctTransform::Move(QVector3D t_pos)
{
    m_localTransform.Translate(t_pos);
    //m_localTransform.GetMatrix().translate(t_pos);
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

ctMatrix4 ctTransform::GetLocalTransformMatrix()// const
{
    return m_localTransform;
}

ctMatrix4 ctTransform::GetGlobalTransformMatrix()// const
{
//    return GetLocalTransformMatrix();
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
