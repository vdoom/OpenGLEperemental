#ifndef CTINPUTEVENT_H
#define CTINPUTEVENT_H

#include <QKeyEvent>
#include <QTouchEvent>
#include <QMouseEvent>

class ctInputEvent
{
public:
    enum inputEventsFlags
    {
        IEF_DEAD_EVENT           = 0x0,
        IEF_MOUSE_EVENT          = 0x1,
        IEF_TOUCH_EVENT          = 0x2,
        IEF_KEY_EVENT            = 0x4,
        IEF_MOUSE_BUTTON_PRESS   = 0x8,
        IEF_MOUSE_BUTTON_RELEASE = 0x10,
        IEF_MOUSE_MOVE           = 0x20
    };
private:
    unsigned int m_flags;
    QKeyEvent m_keyEvent;
    QTouchEvent m_touchEvent;
    QMouseEvent m_mouseEvent;
    quint64 m_timestamp;
    quint64 m_iterationStamp;
public:
    ctInputEvent();
    ctInputEvent(QKeyEvent, unsigned int, quint64);
    ctInputEvent(QTouchEvent, unsigned int, quint64);
    ctInputEvent(QMouseEvent, unsigned int, quint64);
    bool IsKeyEvent();
    bool IsTouchEvent();
    bool IsMouseEvent();
    QKeyEvent GetKeyEvent();
    QMouseEvent GetMouseEvent();
    QTouchEvent GetTouchEvent();
    unsigned int GetFlags();
    void KillEvent();
    bool IsDead();
    quint64 GetTimeStamp();
    quint64 GetIterationStamp();
};

#endif // CTINPUTEVENT_H
