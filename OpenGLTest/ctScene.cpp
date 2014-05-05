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
    if(m_objects)
    {
        QVector<ctObject*>::iterator itor;
        for(itor = m_objects->begin(); itor != m_objects->end(); ++itor)
        {
            delete (*itor);
        }
        if(m_objects->count() > 0)
            m_objects->remove(0, m_objects->count() - 1);
    }
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
    GetTransform()->Scale(QVector3D(1.0f, 1.0f, 1.0f));
    GetTransform()->Move(QVector3D(0.0f, 0.0f, 0.0f));
    for(int i = 0; i < m_objects->size(); ++i)
    {
        ((ctObject*)(*m_objects)[i])->Init();
    }

    for(int i = 0; i < m_components->size(); ++i)
    {
        ((ctEntity*)(*m_components)[i])->Init();
    }

    matrix.ortho((0 - GetWindow()->GetDefaultWidth() /2), (GetWindow()->GetDefaultWidth() /2), (GetWindow()->GetDefaultHeight()/2), (0 - GetWindow()->GetDefaultHeight()/2), 0, 10000.0f);//((0 - GetWindow()->width()/2), (GetWindow()->width()/2), (GetWindow()->height()/2), (0 - GetWindow()->height()/2), 0, 10000.0f);
    //matrix.perspective(60, 4.0/3.0, 0.1, 1000.0);
    matrix.translate(0, 0 , -50);
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
}



void ctScene::AddObject(ctObject * t_objects)
{
    t_objects->SetScene(this);
    if(m_shaderManager) t_objects->SetShaderManager(m_shaderManager);
    m_objects->append(t_objects);
    if(t_objects->GetTransform())
    {
        t_objects->GetTransform()->SetParent(GetTransform());
    }
}

ctObject* ctScene::GetObjectByUUID(QUuid t_uuid)
{
    for(int i = 0; i < m_objects->size(); ++i)
    {
        if((*m_objects)[i]->GetUuid() == t_uuid) return (*m_objects)[i];
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

//------------------------------------------------------------

void ctScene::SetDefault(ctShaderManager * t_shaderManager, ctScene * t_scene, QGLContext * t_OpenGLContext)
{
    ctObject::SetDefault(t_shaderManager, t_scene, t_OpenGLContext);
    m_objects = new QVector<ctObject*>();
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

bool ctScene::IsDragMode()
{
    return m_dragMode;
}

void ctScene::SetDragMode(bool t_dragMode)
{
    m_dragMode = t_dragMode;
}
