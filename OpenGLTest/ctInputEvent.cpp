#include "ctInputEvent.h"
#include "ctTime.h"
ctInputEvent::ctInputEvent() : m_keyEvent(QEvent::None,0,Qt::NoModifier), m_mouseEvent(QEvent::None, QPointF(), Qt::NoButton, Qt::NoButton,Qt::NoModifier), m_touchEvent(QEvent::None), m_iterationStamp(0)
{
    KillEvent();
}

ctInputEvent::ctInputEvent(QKeyEvent t_keyEvent, unsigned int t_flags, quint64 t_iterationStamp) : m_keyEvent(QEvent::None,0,Qt::NoModifier), m_mouseEvent(QEvent::None, QPointF(), Qt::NoButton, Qt::NoButton,Qt::NoModifier), m_touchEvent(QEvent::None)
{
    m_keyEvent = t_keyEvent;
    m_flags = t_flags;
    m_timestamp = ctTime::GetTime()->GetMiliSecsSinceEpoch();
    m_iterationStamp = t_iterationStamp;
}

ctInputEvent::ctInputEvent(QMouseEvent t_mouseEvent, unsigned int t_flags, quint64 t_iterationStamp) : m_keyEvent(QEvent::None,0,Qt::NoModifier), m_mouseEvent(QEvent::None, QPointF(), Qt::NoButton, Qt::NoButton,Qt::NoModifier), m_touchEvent(QEvent::None)
{
    m_mouseEvent = t_mouseEvent;
    m_flags = t_flags;
    m_timestamp = ctTime::GetTime()->GetMiliSecsSinceEpoch();
    m_iterationStamp = t_iterationStamp;
}

ctInputEvent::ctInputEvent(QTouchEvent t_touchEvent, unsigned int t_flags, quint64 t_iterationStamp) : m_keyEvent(QEvent::None,0,Qt::NoModifier), m_mouseEvent(QEvent::None, QPointF(), Qt::NoButton, Qt::NoButton,Qt::NoModifier), m_touchEvent(QEvent::None)
{
    m_touchEvent = t_touchEvent;
    m_flags = t_flags;
    m_timestamp = ctTime::GetTime()->GetMiliSecsSinceEpoch();
    m_iterationStamp = t_iterationStamp;
}

unsigned int ctInputEvent::GetFlags()
{
    return m_flags;
}

void ctInputEvent::KillEvent()
{
    m_flags = 0;
}

bool ctInputEvent::IsDead()
{
    return (m_flags == IEF_DEAD_EVENT);
}

bool ctInputEvent::IsKeyEvent()
{
    return (m_flags & IEF_KEY_EVENT);
}

bool ctInputEvent::IsTouchEvent()
{
    return (m_flags & IEF_TOUCH_EVENT);
}

bool ctInputEvent::IsMouseEvent()
{
    return ((m_flags & IEF_MOUSE_BUTTON_PRESS) || (m_flags & IEF_MOUSE_BUTTON_RELEASE) || (m_flags & IEF_MOUSE_EVENT) || (m_flags & IEF_MOUSE_MOVE));
}

QKeyEvent ctInputEvent::GetKeyEvent()
{
    return m_keyEvent;
}

QMouseEvent ctInputEvent::GetMouseEvent()
{
    return m_mouseEvent;
}

QTouchEvent ctInputEvent::GetTouchEvent()
{
    return m_touchEvent;
}

quint64 ctInputEvent::GetTimeStamp()
{
    return m_timestamp;
}

quint64 ctInputEvent::GetIterationStamp()
{
    return m_iterationStamp;
}
