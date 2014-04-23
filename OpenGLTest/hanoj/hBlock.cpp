#include "hBlock.h"
#include <QDebug>

void Block::SetDefault(ctShaderManager * t_shaders, ctScene * t_scene, QGLContext * t_OGLcontext)
{
    ctClickablePlane::SetDefault(t_shaders, t_scene, t_OGLcontext);
    m_blockColor = BC_BLUE;
    m_blockSize = 7;
    qDebug()<<"Block";
}

Block::Block(ctShaderManager * t_shaders) : ctClickablePlane(t_shaders)
{
}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene) : ctClickablePlane(t_shaders, t_scene)
{}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QGLContext * t_OGLcontext) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext)
{SetDefault(t_shaders, t_scene, t_OGLcontext);}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QGLContext * t_OGLcontext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext, t_AA, t_BB, t_type)
{
    SetDefault(t_shaders, t_scene, t_OGLcontext);
}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QGLContext * t_OGLcontext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type, int t_blockSize, int t_blockColor): ctClickablePlane(t_shaders, t_scene, t_OGLcontext, t_AA, t_BB, t_type)
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
}
void Block::Draw()
{
    ctClickablePlane::Draw();
}
void Block::Init()
{
    ctClickablePlane::Init();
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
