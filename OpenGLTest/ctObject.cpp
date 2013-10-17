#include "ctObject.h"

ctObject::ctObject()
{
}

ctTransform ctObject::GetTransform() const
{return m_transform;}

ctMatrix4 ctObject::GetProjectionMatrix() const
{return m_projectionMatrix;}

void ctObject::SetProjectionMatrix(const ctMatrix4 &t_projMat)
{
    m_projectionMatrix.SetMatrix(t_projMat.GetMatrix());
}

void ctObject::SetProjectionMatrix(const QMatrix4x4 &t_projMat)
{
    m_projectionMatrix.SetMatrix(t_projMat);
}
