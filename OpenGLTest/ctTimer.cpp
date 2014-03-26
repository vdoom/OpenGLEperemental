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
        //TODO: NEED TEST FOR FREEZ UNFREEZ
        //-------------------------------------------------------------------------------------------------
        if(!IsFreezable() || !IsFreezed())
        {
            if(m_counter > ctTime::GetTime()->GetDeltaTime()) m_counter -= ctTime::GetTime()->GetDeltaTime();
            else m_counter = 0;
        }
        //-------------------------------------------------------------------------------------------------

        if( m_counter <= 0)//(m_startTime + m_lifeTime) < ctTime::GetTime()->GetMiliSecsSinceEpoch() )
        {
            if(m_delegat.IsHasActions())
            {
                m_delegat.Call();
            }
            if(m_isCyclic)
            {
                m_counter = m_lifeTime;
                //m_startTime = ctTime::GetTime()->GetMiliSecsSinceEpoch();
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

void ctTimer::SetTimer(quint64 t_lifeTime, bool t_isCyclic)
{
    m_lifeTime = t_lifeTime;
    m_counter = m_lifeTime;
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
