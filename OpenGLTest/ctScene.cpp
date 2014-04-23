#include "ctScene.h"
#include "ctWindow.h"
#include "ctGLWidget.h"

ctScene::ctScene()
{
    SetDefault(0,0,0);
}

ctScene::ctScene(ctShaderManager * t_shaderManager)
{
    SetDefault(t_shaderManager, 0, 0);
}

ctScene::ctScene(ctShaderManager * t_shaderManager, QGLContext * t_OpenGLContext)
{
    SetDefault(t_shaderManager, 0, t_OpenGLContext);
}

ctScene::~ctScene()
{
    qDebug()<<"DestroyScene";
    if(m_components)
    {
        QVector<ctEntity*>::iterator itor;
        for(itor = m_components->begin(); itor != m_components->end(); ++itor)
        {
            delete (*itor);
        }
        m_components->remove(0, m_components->count() - 1);
    }
    if(m_objects)
    {
        QVector<ctObject*>::iterator itor;
        for(itor = m_objects->begin(); itor != m_objects->end(); ++itor)
        {
            delete (*itor);
        }
        m_objects->remove(0, m_objects->count() - 1);
    }
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

void ctScene::BeginDraw()
{
}

void ctScene::Draw()
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        if(((ctObject*)(*m_objects)[i])->GetTransform()->IsVisible())
            ((ctObject*)(*m_objects)[i])->Draw();
    }

//    for(int i = 0; i < m_components->size(); ++i)
//    {
//        ((ctEntity*)(*m_components)[i])->Draw();
//    }
}

void ctScene::EndDraw()
{
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
    t_objects->SetScene(this);
    if(m_shaderManager) t_objects->SetShaderManager(m_shaderManager);
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

void ctScene::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QGLContext * t_OpenGLContext)
{
    ctObject::SetDefault(t_shaderManager, t_scene, t_OpenGLContext);
    m_objects = new QVector<ctObject*>();
    m_components = new QVector<ctEntity*>();
}

void ctScene::SetWindow(ctWindow *t_window)
{
    m_window = t_window;
}

ctWindow * ctScene::GetWindow() const
{
    return m_window;
}

//void ctScene::DrawText(QPointF t_pos, QString t_str)
//{
//    QPainter painter(m_wi);
//    painter.setPen(Qt::green);
//    painter.drawText(t_pos, t_str);
//}

QGLContext * ctScene::GetContext()
{
    return GetWindow()->GetOpenGLContext();
    //qDebug()<<m_GLWidget->context();
    //return m_GLWidget->context();
}
