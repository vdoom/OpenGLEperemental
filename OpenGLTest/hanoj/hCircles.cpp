#include "hCircles.h"
#include "ctMover.h"

hCircles::hCircles() : ctObject()
{
}
hCircles::hCircles(ctShaderManager *t_shaderManager) : ctObject(t_shaderManager)
{}
hCircles::hCircles(ctShaderManager *t_shaderManager, ctScene *t_scene) : ctObject(t_shaderManager, t_scene)
{}
hCircles::hCircles(ctShaderManager *t_shaderManager, ctScene *t_scene, QGLContext *t_GLContext) : ctObject(t_shaderManager, t_scene, t_GLContext)
{}

hCircles::~hCircles()
{
    if(m_circles.count() > 0)
    {
        QVector<ctPlane*>::iterator itor;
        for(itor = m_circles.begin(); itor != m_circles.end(); ++itor)
        {
            delete (*itor);
        }
        m_circles.remove(0, m_circles.count() - 1);
    }
}

void hCircles::Init()
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 1; j < 5; ++j)
        {
            ctPlane* tmpPlane = new ctPlane(GetShaderManager(), GetScene(), GetOpenGLContext(),QVector3D(1,1,1), QVector3D(-1,-1,1), ctPlane::Textured);
            tmpPlane->SetTexture(hCircles::GetCircleResPath(i,j), true);
            tmpPlane->GetTransform()->Scale(QVector3D(0.001f,0.001f,1));
            tmpPlane->GetTransform()->SetParent(GetTransform());
            tmpPlane->Init();
            m_circles.push_back(tmpPlane);
            ctMover * m_mover = new ctMover();
            m_mover->SetUp(QVector3D(1,1,-2), QVector3D(-1, -1, -2), 10000, true, tmpPlane->GetTransform());
            tmpPlane->AddComponnent(m_mover);
            m_mover->Start();
        }
    }
}

void hCircles::Update()
{
    ctObject::Update();
    for(int i = 0; i < m_circles.count(); ++i)
    {
        m_circles[i]->Update();
    }
}

void hCircles::Draw()
{
    ctObject::Draw();
    for(int i = 0; i < m_circles.count(); ++i)
    {
        //qDebug()<<"Draw Circle";
        m_circles[i]->Draw();
    }
}
