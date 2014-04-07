#include "ctInputHelper.h"
#include "ctInput.h"
#include <QVector3D>
#include <QDebug>

ctInputHelper::ctInputHelper(ctInput * t_input)
{
    m_mouseButtons[0] = MBS_NONE;
    m_mouseButtons[1] = MBS_NONE;
    m_mouseButtons[2] = MBS_NONE;

    m_mousePos = QVector2D(0, 0);

    m_input = t_input;
}

void ctInputHelper::ProcessingEvent(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchBegin:
        case QEvent::TouchCancel:
        case QEvent::TouchEnd:
        case QEvent::TouchUpdate:
        {
            QTouchEvent* tmp = static_cast<QTouchEvent *>(event);
            m_touches.clear();
            m_touches.append(tmp->touchPoints());
            break;
        }
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* tmp = static_cast<QMouseEvent *>(event);
            if((tmp->button() & Qt::LeftButton) || (tmp->buttons() & Qt::LeftButton))
            {
                m_mouseButtons[MB_LEFT] = MBS_PUSH;
            }
//            if((tmp->button() & Qt::RightButton) || (tmp->buttons() & Qt::RightButton))
//            {
//                m_mouseButtons[MB_RIGHT] = MBS_PUSH;
//            }
            m_mousePos.setX(tmp->x());
            m_mousePos.setY(tmp->y());
            break;//return true;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* tmp = static_cast<QMouseEvent *>(event);
            if((tmp->button() & Qt::LeftButton) || (tmp->buttons() & Qt::LeftButton))
            {
                m_mouseButtons[MB_LEFT] = MBS_RELEASE;
            }
//            if((tmp->button() & Qt::RightButton) || (tmp->buttons() & Qt::RightButton))
//            {
//                m_mouseButtons[MB_RIGHT] = MBS_RELEASE;
//            }
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
    return GetMouseButtonState(MB_LEFT, MBS_PRESS_N_HOLD);//(m_mouseButtons[MB_LEFT] == MBS_PRESS_N_HOLD);
}

bool ctInputHelper::IsMouseLeftButtonPush() const
{
    return GetMouseButtonState(MB_LEFT, MBS_PUSH);//(m_mouseButtons[MB_LEFT] == MBS_PUSH);
}

bool ctInputHelper::IsMouseLeftButtonRelease() const
{
    return GetMouseButtonState(MB_LEFT, MBS_RELEASE);//(m_mouseButtons[MB_LEFT] == MBS_RELEASE);
}

bool ctInputHelper::IsMouseLeftButtonNoneActive() const
{
    return GetMouseButtonState(MB_LEFT, MBS_NONE);//(m_mouseButtons[MB_LEFT] == MBS_NONE);
}

bool ctInputHelper::IsMouseRightButtonPressNhold() const
{
    return false;//GetMouseButtonState(MB_RIGHT, MBS_PRESS_N_HOLD);
}

bool ctInputHelper::IsMouseRightButtonPush() const
{
    return false;//GetMouseButtonState(MB_RIGHT, MBS_PUSH);
}

bool ctInputHelper::IsMouseRightButtonRelease() const
{
    return false;//GetMouseButtonState(MB_RIGHT, MBS_RELEASE);
}

bool ctInputHelper::IsMouseRightButtonNoneActive() const
{
    return false;//GetMouseButtonState(MB_RIGHT, MBS_NONE);
}

bool ctInputHelper::GetMouseButtonState(int t_button, int t_state) const
{
    return (m_mouseButtons[t_button] == t_state);
}

QList<QTouchEvent::TouchPoint> ctInputHelper::GetTouches() const
{
    return m_touches;
}
// tmp.setX(tmp.x() - (GetWindow()->GetWidth()/2));
QVector2D ctInputHelper::GetMousePos2D() const
{
    return QVector2D((m_mousePos.x() - ((m_input->GetWindow()->GetWidth() / m_input->GetWindow()->GetDevicePixelRatioCoff())  / 2))/* m_input->GetWindow()->GetWidthScale()*/,
                    (m_mousePos.y() - ((m_input->GetWindow()->GetHeight() / m_input->GetWindow()->GetDevicePixelRatioCoff()) / 2))/* m_input->GetWindow()->GetWidthScale()*/);
    //return QVector2D((m_mousePos.x() * m_input->GetWindow()->GetDevicePixelRatioCoff()) - m_input->GetWindow()->GetWidth() / 2,
    //                 m_mousePos.y() * m_input->GetWindow()->GetDevicePixelRatioCoff() - m_input->GetWindow()->GetHeight() / 2);
}

QVector3D ctInputHelper::GetMousePos3D() //const
{
    QVector2D tmp = GetMousePos2D();
    return QVector3D(tmp.x() , tmp.y(), 1);
}
