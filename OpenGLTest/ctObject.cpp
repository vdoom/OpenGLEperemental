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

    if(m_components)
    {
        QVector<ctEntity*>::iterator itor;
        for(itor = m_components->begin(); itor != m_components->end(); ++itor)
        {
            delete (*itor);
        }
        if(m_components->count()>0)
            m_components->remove(0, m_components->count() - 1);
    }
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

void ctObject::SetOpenGLContext(const QOpenGLContext *t_context)
{
    m_OpenGLContext = const_cast<QOpenGLContext*>(t_context);
}

void ctObject::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QOpenGLContext * t_OpenGLContext)
{
    m_shaderManager = t_shaderManager;
    m_scene = t_scene;
    m_OpenGLContext = t_OpenGLContext;
    m_transform = new ctTransform(this);
    m_components = new QVector<ctEntity*>();
    Show();
}

ctEntity* ctObject::Clone()
{
//    ctObject* tmp = new ctObject(GetShaderManager(), GetScene(), GetOpenGLContext());//(ctObject*)ctEntity::Clone();
//    tmp->SetName(GetName() + QString("_Clone"));
//    tmp->SetProjectionMatrix(GetProjectionMatrix());
//    tmp->GetTransform()->SetLocalMatrix(m_transform->GetLocalTransformMatrix());
//    tmp->GetTransform()->SetParent(m_transform->GetParent());
//    return (ctEntity*)tmp;
    return this;
}

void ctObject::Show()
{
    m_isVisible = true;
}

void ctObject::Hide()
{
    m_isVisible = false;
}

bool ctObject::IsVisible()
{
    bool parentVisible = true;
    if(GetTransform()->GetParent())
    {
        parentVisible = GetTransform()->GetParent()->GetGameObject()->IsVisible();
    }
    if(!m_isVisible) return false;
    return m_isVisible && parentVisible;
}

QVector<ctEntity*> ctObject::GetComponentByName(QString t_name)
{
    QVector<ctEntity*> tmp;
    for(int i = 0; i < m_components->size(); ++i)
    {
        if((*m_components)[i]->GetName() == t_name)
        {tmp.append((*m_components)[i]);}
    }
    return tmp;
}

template<class T> QVector<T*> ctObject::GetComponnetsByType()
{
    QVector<T*> tmp;
    for(int i = 0; i < m_components->size(); ++i)
    {
        T* tmpVar = dynamic_cast<T*>((*m_components)[i]);
        if(tmp)
        {
            tmp.append(tmpVar);
        }
    }
    return tmp;
}

ctEntity* ctObject::GetComponentByUUID(QUuid t_uuid)
{
    for(int i = 0; i < m_components->size(); ++i)
    {
        if((*m_components)[i]->GetUuid() == t_uuid) return (*m_components)[i];
    }
    return 0;
}

void ctObject::AddComponnent(ctEntity * t_entity)
{
    m_components->append(t_entity);
}

void ctObject::Update()
{
    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)(*m_components)[i])->Update();
    }
}
