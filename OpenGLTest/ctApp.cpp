#include "ctApp.h"
#include "ctScene.h"

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
