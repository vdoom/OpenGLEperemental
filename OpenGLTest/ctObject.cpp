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

void ctObject::Freeze()
{
    ctEntity::Freeze();
}

void ctObject::Unfreeze()
{
    ctEntity::Unfreeze();
}

void ctObject::SetScene(ctScene *t_scene)
{
    m_scene = t_scene;
}

ctScene * ctObject::GetScene() const
{
    return m_scene;
}

void ctObject::SetShaderManager(ctShaderManager *t_shaderManager)
{
    m_scene = t_shaderManager;
}

ctShaderManager * ctObject::GetShaderManager() const
{
    return m_shaderManager;
}
