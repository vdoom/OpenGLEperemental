#include "ctInput.h"
#include <QDebug>

ctInput::ctInput(ctWindow * t_window, QWidget * parent) : QWidget(parent), m_helper(this)
{
    m_iterationStamp = 1;
    m_window = t_window;
	qDebug()<<"\nCreate Input \n";
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
    for(int i = 0; i < 255; ++i)
    {
        if(m_eventsPool[i].GetIterationStamp() != m_iterationStamp)
        {
            m_eventsPool[i].KillEvent();
        }
    }
    if(m_iterationStamp != 0) ++m_iterationStamp;
    else m_iterationStamp += 2;

    m_helper.Update();
}

void ctInput::PostUpdate()
{
   // m_touchEvent.clear();
   // m_mouseEvent.clear();
   // m_keyEvent.clear();
}

bool ctInput::event(QEvent *event)
{
    m_helper.ProcessingEvent(event);
//    switch (event->type())
//    {
//    case QEvent::TouchBegin:
//        {
//            m_lastTouchState = ctInput::ctInputTouchBegin;
//            m_lastTouchEvent = static_cast<QTouchEvent *>(event);
//            //m_touchEvent.append(static_cast<QTouchEvent *>(event));
//            QList<QTouchEvent::TouchPoint> touchPoints = m_lastTouchEvent->touchPoints();//static_cast<QTouchEvent *>(event)->touchPoints();
//            qDebug()<<"TouchBegin"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
//            return true;
//        }
//    case QEvent::TouchUpdate:
//        {
//            m_lastTouchState = ctInput::ctInputTouchUpdate;
//            m_lastTouchEvent = static_cast<QTouchEvent *>(event);
//            //m_touchEvent.append(static_cast<QTouchEvent *>(event));
//            QList<QTouchEvent::TouchPoint> touchPoints = m_lastTouchEvent->touchPoints();
//            //qDebug()<<"TouchUpdate"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
//            return true;
//        }
//    case QEvent::TouchEnd:
//        {
//            m_lastTouchState = ctInput::ctInputTouchEnd;
//            m_lastTouchEvent = static_cast<QTouchEvent *>(event);
//            //m_touchEvent.append(static_cast<QTouchEvent *>(event));
//            QList<QTouchEvent::TouchPoint> touchPoints = m_lastTouchEvent->touchPoints();
//            //qDebug()<<"TouchEnd"<<touchPoints[0].pos().x()<<" "<< touchPoints[0].pos().y();
//            return true;
//        }
//    case QEvent::MouseButtonPress:
//        {
//            m_lastMouseEvent = static_cast<QMouseEvent *>(event);
//            //qDebug()<<"MousePress :"<<m_lastMouseEvent->x()<<" "<<m_lastMouseEvent->y()<<" "<<m_lastMouseEvent->button();
//            AddEvent(ctInputEvent(*m_lastMouseEvent, (unsigned int)(ctInputEvent::IEF_MOUSE_EVENT | ctInputEvent::IEF_MOUSE_BUTTON_PRESS), m_iterationStamp));
//            return true;
//        }
//     case QEvent::MouseButtonRelease:
//        {
//            m_lastMouseEvent = static_cast<QMouseEvent *>(event);
//            //qDebug()<<"MouseButtonRelease :"<<m_lastMouseEvent->x()<<" "<<m_lastMouseEvent->y()<<" "<<m_lastMouseEvent->button();
//            AddEvent(ctInputEvent(*m_lastMouseEvent, (unsigned int)(ctInputEvent::IEF_MOUSE_EVENT | ctInputEvent::IEF_MOUSE_BUTTON_RELEASE), m_iterationStamp));
//            return true;
//        }
//     case QEvent::MouseMove:
//        {
//            m_lastMouseEvent = static_cast<QMouseEvent *>(event);
//            //qDebug()<<"MouseMove :"<<m_lastMouseEvent->x()<<" "<<m_lastMouseEvent->y();
//            AddEvent(ctInputEvent(*m_lastMouseEvent, (unsigned int)(ctInputEvent::IEF_MOUSE_EVENT | ctInputEvent::IEF_MOUSE_MOVE), m_iterationStamp));
//            return true;
//        }
//    case QEvent::Resize:
//        {
//            AddEvent(ctInputEvent(ctInputEvent::IEF_CHANGE_SCEEN_SIZE, m_iterationStamp));
//            return true;
//        }
//    case QEvent::OrientationChange:
//        {
//        //qDebug()<<"hange size";
//            AddEvent(ctInputEvent(ctInputEvent::IEF_ORIENTATION_CHANGE, m_iterationStamp));
//            return true;
//        }
//     default:
//            return QWidget::event(event);
//            return true;
//    }
}

QTouchEvent * ctInput::GetTouchEvent() const
{
    return m_lastTouchEvent;
}

QMouseEvent * ctInput::GetMouseEvent() const
{
    return m_lastMouseEvent;
}

int ctInput::GetIndexOfDeadEvent()
{
    for(int i = 0; i < 255; ++i)
    {
        if(m_eventsPool[i].IsDead()) return i;
    }
    return -1;
}

void ctInput::AddEvent(ctInputEvent t_event)
{
    int indexFree = GetIndexOfDeadEvent();
    if(indexFree < 0)
    {
        qDebug()<<"Errore: Can't Add new event!!!";
        return;
    }
    else
    {
        m_eventsPool[indexFree] = t_event;
    }
}

QVector<ctInputEvent> ctInput::GetEvents(unsigned int t_flags)
{
    QVector<ctInputEvent> tmp;
    for(int i = 0; i < 255; ++i)
    {
        if(m_eventsPool[i].GetFlags() & t_flags)
        {
            tmp.append(m_eventsPool[i]);
        }
    }
    //qDebug()<<tmp.size();
    return tmp;
}

ctInputHelper ctInput::GetInputHelper() const
{
    return m_helper;
}

void ctInput::SetWindow(ctWindow* t_window)
{
    m_window = t_window;
}

ctWindow* ctInput::GetWindow() const
{
    return m_window;
}
