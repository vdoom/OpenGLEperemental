#include "ctObject.h"

ctObject::ctObject()
{
    m_transform = new ctTransform(this);
}

ctObject::~ctObject()
{
    delete m_transform;
}

ctTransform * ctObject::GetTransform()// const
{return m_transform;}

ctMatrix4 ctObject::GetProjectionMatrix()// const
{return m_projectionMatrix;}

void ctObject::SetProjectionMatrix(ctMatrix4 &t_projMat)
{
    m_projectionMatrix.SetMatrix(t_projMat.GetMatrix());
}

void ctObject::SetProjectionMatrix(QMatrix4x4 &t_projMat)
{
    m_projectionMatrix.SetMatrix(t_projMat);
}

QString ctObject::GetTypeName()
{
    return QString("ctObject");
}

void ctObject::Freeze()
{
    ctEntity::Freeze();
}

void ctObject::Unfreeze()
{
    ctEntity::Unfreeze();
}
