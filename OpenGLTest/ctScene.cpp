#include "ctScene.h"

ctScene::ctScene()
{
    m_objects = QVector<ctObject*>();
    m_components = QVector<ctEntity*>();
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
        ((ctObject*)m_objects[i])->Init();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)m_components[i])->Init();
    }
}

void ctScene::Draw()
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        ((ctObject*)m_objects[i])->Draw();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)m_components[i])->Draw();
    }
}

void ctScene::Update()
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        ((ctObject*)m_objects[i])->Update();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)m_components)->Update();
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
