#include "ctInputHelper.h"
#include <QVector3D>

ctInputHelper::ctInputHelper()
{
    m_mouseButtons[0] = MBS_NONE;
    m_mouseButtons[1] = MBS_NONE;
    m_mouseButtons[2] = MBS_NONE;

    m_mousePos = QVector2D(0, 0);
}

void ctInputHelper::ProcessingEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* tmp = static_cast<QMouseEvent *>(event);
            if((tmp->button() & Qt::LeftButton) || (tmp->buttons() & Qt::LeftButton))
            {
                m_mouseButtons[0] = MBS_PUSH;
            }
            m_mousePos.setX(tmp->x());
            m_mousePos.setY(tmp->y());
            break;//return true;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* tmp = static_cast<QMouseEvent *>(event);
            if((tmp->button() & Qt::LeftButton) || (tmp->buttons() & Qt::LeftButton))
            {
                m_mouseButtons[0] = MBS_RELEASE;
            }
            m_mousePos.setX(tmp->x());
            m_mousePos.setY(tmp->y());
            break;//return true;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent* tmp = static_cast<QMouseEvent *>(event);
            m_mousePos = QVector2D(tmp->x(), tmp->y());
        }
        default:
            break;//return;
    }
}

void ctInputHelper::Update()
{
    for(int i = 0; i < 3; ++i)
    {
        if(m_mouseButtons[i] == MBS_PUSH)
            m_mouseButtons[i] == MBS_PRESS_N_HOLD;

        if(m_mouseButtons[i] == MBS_RELEASE)
            m_mouseButtons[i] = MBS_NONE;
    }
}

bool ctInputHelper::IsMouseLeftButtonPressNhold() const
{
    return (m_mouseButtons[0] == MBS_PRESS_N_HOLD);
}

bool ctInputHelper::IsMouseLeftButtonPush() const
{
    return (m_mouseButtons[0] == MBS_PUSH);
}

bool ctInputHelper::IsMouseLeftButtonRelease() const
{
    return (m_mouseButtons[0] == MBS_RELEASE);
}

bool ctInputHelper::IsMouseLeftButtonNoneActive() const
{
    return (m_mouseButtons[0] == MBS_NONE);
}

QVector2D ctInputHelper::GetMousePos2D() const
{
    return m_mousePos;
}

QVector3D ctInputHelper::GetMousePos3D() //const
{
    QVector3D tmp = QVector3D(m_mousePos.x(), m_mousePos.y(), 1);
    return tmp;
}
