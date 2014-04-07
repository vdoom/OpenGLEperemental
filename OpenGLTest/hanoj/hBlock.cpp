#include "Block.h"

void Block::SetDefault(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext)
{
    ctClickablePlane::SetDefault(t_shaders, t_scene, t_OGLcontext);
}

Block::Block(ctShaderManager * t_shaders) : ctClickablePlane(t_shaders)
{
}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene) : ctClickablePlane(t_shaders, t_scene)
{}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext)
{}
Block::Block(ctShaderManager * t_shaders, ctScene * t_scene, QOpenGLContext * t_OGLcontext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext, t_AA, t_BB, t_type)
{
    SetDefault(t_shaders, t_scene, t_OGLcontext);
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
