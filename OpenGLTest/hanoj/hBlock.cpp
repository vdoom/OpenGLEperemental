#include "hBlock.h"
#include <QDebug>

void Block::SetDefault(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext)
{
    ctClickablePlane::SetDefault(t_shaders, t_scene, t_OGLcontext);
    m_blockColor = BC_BLUE;
    m_blockSize = 7;
    //qDebug()<<"Block";
    m_mover = 0;
    m_mover = new ctMover();

}

Block::Block(ctShaderManager * t_shaders) : ctClickablePlane(t_shaders)
{
}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene) : ctClickablePlane(t_shaders, t_scene)
{}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext)
{SetDefault(t_shaders, t_scene, t_OGLcontext);}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext, t_AA, t_BB, t_type)
{
    SetDefault(t_shaders, t_scene, t_OGLcontext);
}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type, int t_blockSize, int t_blockColor): ctClickablePlane(t_shaders, t_scene, t_OGLcontext, t_AA, t_BB, t_type)
{
    SetDefault(t_shaders, t_scene, t_OGLcontext);
	m_blockColor = t_blockColor;
	m_blockSize = t_blockSize;
}

Block::~Block()
{}

void Block::Update()
{
    ctClickablePlane::Update();
//	if(m_blockColor == 2 && m_blockSize == 2)
//	{
//		qDebug()<<G_indexqqq;
//	}
}
void Block::Draw()
{
    //qDebug()<<"DrawBlock";
    ctClickablePlane::Draw();
}
void Block::Init()
{
    ctClickablePlane::Init();
    m_mover->SetUp(QVector3D(100,10,1), QVector3D(-1,-1,1), 100, false, GetTransform(), 0);
    m_mover->Init();
    AddComponnent(m_mover);
}
ctEntity* Block::Clone()
{
    return 0;
}

int Block::GetBlockColor() const
{
    return m_blockColor;
}

int Block::GetBlockSize() const
{
    return m_blockSize;
}

void Block::AutoMove(QVector3D t_start, QVector3D t_end)
{
    //if(m_mover)
    //{
    //qDebug()<<"AutoMove from"<<t_start<<" to:"<<t_end;
        m_mover->SetNewPoses(t_start, t_end);
        m_mover->Start();
    //}
}
