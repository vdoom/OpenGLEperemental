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
}

void ctScene::Unfreeze()
{
    ctObject::Unfreeze();
}

QString ctScene::GetTypeName()
{
    return QString("ctScene");
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

//TODO: NEED DEFINE FUNCTIONS GETING BY TYPE!!!!
