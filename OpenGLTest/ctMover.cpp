#include "ctMover.h"
#include <QDebug>

ctMover::ctMover() : m_paretnTransform(0)
{
    m_startPos = QVector3D(0,0,0);
    m_endPos = QVector3D(0,0,0);
    m_elapsed = 0;
    m_duration = 0;
    m_currentPos = 0;
    m_isCyclic = false;
    m_isWorking = false;
}
ctMover::~ctMover()
{}

void ctMover::Update()
{
    if(m_isWorking)
    {
        m_elapsed += ctTime::GetTime()->GetDeltaTime();
        float tmpMult = m_elapsed / m_duration;
        if(tmpMult > 1) tmpMult = 1;
        if(m_paretnTransform)
        {
            m_paretnTransform->Move(m_startPos + (m_delta * tmpMult));
        }
        if(tmpMult >= 1)
        {
            m_OnFinish.Call();
            if(m_isCyclic)
            {
                m_elapsed = 0;
            }
            else
            {
                m_isWorking = false;
            }
        }
    }
}

void ctMover::SetUp(QVector3D t_startPos, QVector3D t_endPos, float t_time, bool t_cyclic, ctTransform * t_transform)
{
    m_startPos = t_startPos;
    m_endPos = t_endPos;
    m_duration = t_time;
    m_isCyclic = t_cyclic;
    m_paretnTransform = t_transform;
    m_delta = t_endPos - t_startPos;
}

void ctMover::SetTransform(ctTransform * t_transform)
{
    m_paretnTransform = t_transform;
}
void ctMover::Start()
{
    m_isWorking = true;
    m_elapsed = 0;//+= ctTime::GetTime()->GetDeltaTime();
    //m_startTime = ctTime::GetTime()->GetMiliSecsSinceEpoch();
    //m_endTime = m_start
}
void ctMover::Stop()
{
    m_isWorking = false;
}
bool ctMover::IsCyclic()
{
    return m_isCyclic;
}
void ctMover::SetCyclic(bool t_isCyclic)
{
    m_isCyclic = t_isCyclic;
}
bool ctMover::IsWork()
{
    return m_isWorking;
}
ctFastDelegat* ctMover::GetDelegatOnFinish()
{
    return &m_OnFinish;
}
