#include "ctTimer.h"
#include "ctTime.h"

ctTimer::ctTimer() : m_isAlive(0)
{
}

void ctTimer::Draw()
{}

void ctTimer::Update()
{
    if(m_isAlive)
    {
        if( (m_startTime + m_lifeTime) < ctTime::GetTime()->GetMiliSecsSinceEpoch() )
        {
            if(true)
            {
                m_delegat.Call();//m_delegat();
            }
            if(m_isCyclic)
            {
                m_startTime = ctTime::GetTime()->GetMiliSecsSinceEpoch();
            }
            else
            {
                m_isAlive = false;
            }
        }
    }
}

void ctTimer::Init()
{}

void ctTimer::SetTimer(quint64 t_lifetime, bool t_isCyclic)
{
    m_lifeTime = t_lifetime;
    m_isAlive = true;
    m_startTime = ctTime::GetTime()->GetMiliSecsSinceEpoch();
    m_isCyclic = t_isCyclic;
}

ctFastDelegat* ctTimer::GetDelegat()
{
    return &m_delegat;
}

void ctTimer::StopTimer()
{
    m_isAlive = false;
}
