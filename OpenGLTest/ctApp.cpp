#include "ctApp.h"
#include "ctScene.h"
#include "ctWindow.h"

ctApp::ctApp()
{

}

ctApp::~ctApp()
{}

ctApp::Init()
{}

ctApp::Update()
{
    m_mainScene->Update();
}

void ctApp::Start()
{
    if(m_mainGameWindow)
    {
        while (true)
        {
            m_mainGameWindow->Draw();//perheps Use Render
            Update();// TODO: need calc in parallel thrid
        }
    }
}
