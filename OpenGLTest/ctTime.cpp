#include "ctTime.h"

ctTime::ctTime()
{
    m_dateTime = new QDateTime(QDateTime::currentDateTime());
    m_prevUpdateTime = m_dateTime->toMSecsSinceEpoch();
}

ctTime::ctTime(const ctTime &t_time)
{
    m_dateTime = new QDateTime(QDateTime::currentDateTime());
    m_prevUpdateTime = m_dateTime->toMSecsSinceEpoch();
}

void ctTime::operator = (ctTime t_time)
{}

ctTime::~ctTime()
{
    delete m_dateTime;
}

void ctTime::Update()
{
    m_prevUpdateTime = m_dateTime->toMSecsSinceEpoch();
}

quint64 ctTime::GetMiliSecsSinceEpoch() const
{
    return m_dateTime->toMSecsSinceEpoch();
}

QString ctTime::DateTimeToStr() const
{
    return m_dateTime->toString("dd.MM.yyyy-hh:mm:ss.zzz");
}

quint64 ctTime::GetDeltaTime() const
{
    return m_dateTime->toMSecsSinceEpoch() - m_prevUpdateTime;
}
