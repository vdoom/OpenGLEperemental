#include "ctInput.h"
#include <QDebug>

ctInput::ctInput(QWidget * parent) : QWidget(parent)
{
}

ctInput::~ctInput()
{

}

QVector<QMouseEvent *> ctInput::GetMouseEvent()
{
    return m_mouseEvent;
}

QVector<QKeyEvent *> ctInput::GetKeyEvent()
{
    return m_keyEvent;
}

QVector<QTouchEvent *> ctInput::GetTouchEvent()
{
    return m_touchEvent;
}

void ctInput::Update()
{

}

void ctInput::PostUpdate()
{
    m_touchEvent.clear();
    m_mouseEvent.clear();
    m_keyEvent.clear();
}

bool ctInput::event(QEvent *event)
{
    //m_touchEvent.clear();

    switch (event->type())
    {
    case QEvent::TouchBegin:
        {
            m_touchEvent.append(static_cast<QTouchEvent *>(event));
            QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
            qDebug()<<"TouchBegin"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
            return true;
        }
    case QEvent::TouchUpdate:
        {
            m_touchEvent.append(static_cast<QTouchEvent *>(event));
            QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
            qDebug()<<"TouchUpdate"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
            return true;
        }
    case QEvent::TouchEnd:
        {
            m_touchEvent.append(static_cast<QTouchEvent *>(event));
            QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
            qDebug()<<"TouchEnd"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
            return true;
        }
    case QEvent::MouseButtonPress:
        {
            QMouseEvent * tmpMouseEvent = static_cast<QMouseEvent *>(event);
            m_mouseEvent.append(tmpMouseEvent);
            qDebug()<<"MousePress :"<<tmpMouseEvent->x()<<" "<<tmpMouseEvent->y();
        }
     default:
            return QWidget::event(event);
    }
}
