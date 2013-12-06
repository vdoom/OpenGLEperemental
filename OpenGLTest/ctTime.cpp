#include "ctTime.h"

ctTime::ctTime()
{
    m_dateTime = new QDateTime(QDateTime::currentDateTime());
    m_prevUpdateTime = GetMiliSecsSinceEpoch();
}

ctTime::ctTime(const ctTime &t_time)
{
    m_dateTime = new QDateTime(QDateTime::currentDateTime());
    m_prevUpdateTime = GetMiliSecsSinceEpoch();
}

//TODO: NEED REFINE!!!
void ctTime::operator = (ctTime t_time)
{}

ctTime::~ctTime()
{
    delete m_dateTime;
}

void ctTime::Update()
{
    m_prevUpdateTime = GetMiliSecsSinceEpoch();
}

quint64 ctTime::GetMiliSecsSinceEpoch() const
{
    return m_dateTime->currentMSecsSinceEpoch();
}

QString ctTime::DateTimeToStr() const
{
    return m_dateTime->toString("dd.MM.yyyy-hh:mm:ss.zzz");
}

quint64 ctTime::GetDeltaTime() const
{
    return GetMiliSecsSinceEpoch() - m_prevUpdateTime;
}
