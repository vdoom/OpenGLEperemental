#include "ctObject.h"
#include <QOpenGLContext>

ctObject::ctObject()
{
    SetDefault(0,0,0);
}

ctObject::ctObject(ctShaderManager * t_shaderManager)
{
    SetDefault(t_shaderManager, 0, 0);
}

ctObject::ctObject(ctShaderManager * t_shaderManager, ctScene * t_scene)
{
    SetDefault(t_shaderManager, t_scene, 0);
}

ctObject::ctObject(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    SetDefault(t_shaderManager, t_scene, t_OpenGLContext);
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
    m_shaderManager = t_shaderManager;
}

ctShaderManager * ctObject::GetShaderManager() const
{
    return m_shaderManager;
}

QOpenGLContext * ctObject::GetOpenGLContext() const
{
    return m_OpenGLContext;
}

void ctObject::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    m_shaderManager = t_shaderManager;
    m_scene = t_scene;
    m_OpenGLContext = t_OpenGLContext;
    m_transform = new ctTransform(this);
}

ctEntity* ctObject::Clone()
{
    ctEntity* tmp = ctEntity::Clone();
    return tmp;
}
