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
                m_delegat();
            }
            m_isAlive = false;
        }
    }
}

void ctTimer::Init()
{}

void ctTimer::SetTimer(quint64 t_lifetime)
{
    m_lifeTime = t_lifetime;
    m_isAlive = true;
    m_startTime = ctTime::GetTime()->GetMiliSecsSinceEpoch();
}

ctFastDelegat* ctTimer::GetDelegat()
{
    return &m_delegat;
}
