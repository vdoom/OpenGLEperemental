#include "ctInput.h"
#include <QDebug>

ctInput::ctInput(QWidget * parent) : QWidget(parent)
{
}

ctInput::~ctInput()
{

}

//QVector<QMouseEvent *> ctInput::GetMouseEvent()
//{
//    return m_mouseEvent;
//}

QVector<QKeyEvent *> ctInput::GetKeyEvent()
{
    return m_keyEvent;
}

//QVector<QTouchEvent *> ctInput::GetTouchEvent()
//{
//    return m_touchEvent;
//}

void ctInput::Update()
{

}

void ctInput::PostUpdate()
{
   // m_touchEvent.clear();
   // m_mouseEvent.clear();
   // m_keyEvent.clear();
}

bool ctInput::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::TouchBegin:
        {
            m_lastTouchState = ctInput::ctInputTouchBegin;
            m_lastTouchEvent = static_cast<QTouchEvent *>(event);
            //m_touchEvent.append(static_cast<QTouchEvent *>(event));
            QList<QTouchEvent::TouchPoint> touchPoints = m_lastTouchEvent->touchPoints();//static_cast<QTouchEvent *>(event)->touchPoints();
            qDebug()<<"TouchBegin"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
            return true;
        }
    case QEvent::TouchUpdate:
        {
            m_lastTouchState = ctInput::ctInputTouchUpdate;
            m_lastTouchEvent = static_cast<QTouchEvent *>(event);
            //m_touchEvent.append(static_cast<QTouchEvent *>(event));
            QList<QTouchEvent::TouchPoint> touchPoints = m_lastTouchEvent->touchPoints();
            qDebug()<<"TouchUpdate"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
            return true;
        }
    case QEvent::TouchEnd:
        {
            m_lastTouchState = ctInput::ctInputTouchEnd;
            m_lastTouchEvent = static_cast<QTouchEvent *>(event);
            //m_touchEvent.append(static_cast<QTouchEvent *>(event));
            QList<QTouchEvent::TouchPoint> touchPoints = m_lastTouchEvent->touchPoints();
            qDebug()<<"TouchEnd"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
            return true;
        }
    case QEvent::MouseButtonPress:
        {
            m_lastMouseEvent = static_cast<QMouseEvent *>(event);
            //QMouseEvent * tmpMouseEvent = static_cast<QMouseEvent *>(event);
            //m_mouseEvent.append(tmpMouseEvent);
            qDebug()<<"MousePress :"<<m_lastMouseEvent->x()<<" "<<m_lastMouseEvent->y();
        }
     default:
            return QWidget::event(event);
    }
}

QTouchEvent * ctInput::GetTouchEvent() const
{
    return m_lastTouchEvent;
}

QMouseEvent * ctInput::GetMouseEvent() const
{
    return m_lastMouseEvent;
}
