#include "ctButton.h"
#include "ctInput.h"

#define Input m_input->GetInputHelper()

ctButton::ctButton(ctShaderManager *t_shaders) : ctClickablePlane(t_shaders)
{}
ctButton::ctButton(ctShaderManager *t_shaders, ctScene *t_scene) : ctClickablePlane(t_shaders, t_scene)
{}
ctButton::ctButton(ctShaderManager *t_shaders, ctScene *t_scene, QGLContext *t_OGLcontext) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext)
{}
ctButton::ctButton(ctShaderManager *t_shaders, ctScene *t_scene, QGLContext *t_OGLcontext, QVector3D t_AA, QVector3D t_BB, PlaneType t_type, ctInput* t_input) : ctClickablePlane(t_shaders, t_scene, t_OGLcontext, t_AA, t_BB, t_type)
{
    m_input = t_input;
}

ctFastDelegat* ctButton::GetOnPush()
{
    return &m_OnPush;
}

void ctButton::Update()
{
    ctClickablePlane::Update();
    static bool prevStatePush = false;
    if(Input.IsMouseLeftButtonPush() && IsIntersect(Input.GetMousePos3D()) && !prevStatePush)
    {
        m_OnPush.Call();
        prevStatePush = true;
    }
    if(Input.IsMouseLeftButtonRelease())
    {
        prevStatePush = false;
    }

    //TODO: Check click & call OnPush || OnClick
}
