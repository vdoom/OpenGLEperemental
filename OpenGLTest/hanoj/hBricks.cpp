#include "hBricks.h"

hBricks::hBricks() : ctObject()
{}
hBricks::hBricks(ctShaderManager * t_shaders) : ctObject(t_shaders)
{}
hBricks::hBricks(ctShaderManager * t_shader, ctScene * t_scene) : ctObject(t_shader, t_scene)
{}
hBricks::hBricks(ctShaderManager * t_shader, ctScene * t_scene, QGLContext * t_OpenGLContext) : ctObject(t_shader, t_scene, t_OpenGLContext)
{}

hBricks::~hBricks()
{}

void hBricks::Update()
{
    ctObject::Update();
}
void hBricks::Draw()
{
    ctObject::Update();
}
void hBricks::Init()
{
    ctObject::Update();
}
