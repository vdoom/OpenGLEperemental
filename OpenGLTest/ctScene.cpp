#include "ctScene.h"

ctScene::ctScene()
{
    m_objects = new QVector<ctObject*>();
    m_components = new QVector<ctEntity*>();
}

ctScene::~ctScene()
{
    //TODO: NEED DESTROY OBJECTS
}

void ctScene::Freeze()
{
    ctObject::Freeze();
    for(int i = 0; i < m_objects->size(); ++i)
    {
        (*m_objects)[i]->Freeze();
    }
    for(int i = 0; i < m_components->size(); ++i)
    {
        (*m_components)[i]->Freeze();
    }
}

void ctScene::Unfreeze()
{
    ctObject::Unfreeze();
    for(int i = 0; i < m_objects->size(); ++i)
    {
        (*m_objects)[i]->Unfreeze();
    }
    for(int i = 0; i < m_components->size(); ++i)
    {
        (*m_components)[i]->Unfreeze();
    }
}

void ctScene::Init()
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        ((ctObject*)(*m_objects)[i])->Init();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)(*m_components)[i])->Init();
    }
}

void ctScene::Draw()
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        ((ctObject*)(*m_objects)[i])->Draw();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)(*m_components)[i])->Draw();
    }
}

void ctScene::Update()
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        ((ctObject*)(*m_objects)[i])->Update();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)(*m_components)[i])->Update();
    }
}


void ctScene::AddComponnent(ctEntity * t_entity)
{
    m_components->append(t_entity);
}

void ctScene::AddObject(ctObject * t_objects)
{
    m_objects->append(t_objects);
}

ctObject* ctScene::GetObjectByUUID(QUuid t_uuid)
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        if((*m_objects)[i]->GetUuid() == t_uuid) return (*m_objects)[i];
    }
    return 0;
}

ctEntity* ctScene::GetComponentByUUID(QUuid t_uuid)
{
    for(int i = 0; i < m_components->size(); ++i)
    {
        if((*m_components)[i]->GetUuid() == t_uuid) return (*m_components)[i];
    }
    return 0;
}

QVector<ctObject*> ctScene::GetObjectsByName(QString t_name)
{
    QVector<ctObject*> tmp;
    for(int i = 0; i < m_objects->size(); ++i)
    {
        if((*m_objects)[i]->GetName() == t_name)
        {tmp.append((*m_objects)[i]);}
    }
    return tmp;
}

QVector<ctEntity*> ctScene::GetComponentByName(QString t_name)
{
    QVector<ctEntity*> tmp;
    for(int i = 0; i < m_objects->size(); ++i)
    {
        if((*m_components)[i]->GetName() == t_name)
        {tmp.append((*m_components)[i]);}
    }
    return tmp;
}

//TODO: NEED TEST!!!
//----------------------------------------------------------
template<class T> QVector<T*> ctScene::GetObjectsByType()
{
    QVector<T*> tmp;
    for(int i = 0; i < m_objects->size(); ++i)
    {
        T* tmpVar = dynamic_cast<T*>((*m_objects)[i]);
        if(tmpVar)
        {
            tmp.append(tmpVar);
        }
    }
    return tmp;
}

template<class T> QVector<T*> ctScene::GetComponnetsByType()
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
//------------------------------------------------------------
void ctScene::SetShaderManager(ctShaderManager *t_shaderManager)
{
    m_shaderManager = t_shaderManager;
}

ctShaderManager * ctScene::GetShaderManager() const
{
    return m_shaderManager;
}
