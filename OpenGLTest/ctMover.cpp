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
	static bool first = false;
    if(m_isWorking)
    {
        float tmpMult = m_elapsed / m_duration;
        if(tmpMult > 1) tmpMult = 1;
        if(m_paretnTransform)
        {
            m_paretnTransform->Move(m_startPos + (m_delta * tmpMult));
        }
        if(tmpMult >= 1)
        {
            //m_OnFinish.Call();
            if(m_isCyclic)
            {
                m_elapsed = 0;
            }
            else
            {
                m_isWorking = false;
            }
        }
		if(!first)
		{
			first = true;
		}
		else
		{
			m_elapsed += ctTime::GetTime()->GetDeltaTime();
		}
    }
}

void ctMover::SetUp(QVector3D t_startPos, QVector3D t_endPos, float t_time, bool t_cyclic, ctTransform * t_transform, float t_elaps)
{
    m_duration = t_time;
    m_isCyclic = t_cyclic;
    m_paretnTransform = t_transform;
    SetNewPoses(t_startPos, t_endPos);
    m_prevElapsed = t_elaps;
    //if(t_elaps != 0)
    {
        SetElapse(t_elaps);
    }
}

void ctMover::SetTransform(ctTransform * t_transform)
{
    m_paretnTransform = t_transform;
}
void ctMover::Start()
{
    m_isWorking = true;
    if(m_prevElapsed == 0)
    {
        m_elapsed = 0;
    }
    else
    {
        SetElapse(m_prevElapsed);
    }
   // m_elapsed = 0;
    //m_elapsed = 0;//+= ctTime::GetTime()->GetDeltaTime();
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
void ctMover::SetElapse(float t_elaps)
{
    m_elapsed = m_duration * t_elaps;
}
void ctMover::SetNewPoses(QVector3D t_start, QVector3D t_end)
{
    m_startPos = t_start;
    m_endPos = t_end;
    m_delta = t_end - t_start;
}
