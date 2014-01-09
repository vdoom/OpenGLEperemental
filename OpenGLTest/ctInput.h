#ifndef CTINPUT_H
#define CTINPUT_H

#include <QMouseEvent>
#include <QVector>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QWidget>

//class TriangleWindow;
#include "ctInputEvent.h"
#include "ctInputHelper.h"
#include "ctWindow.h"

class ctInput : public QWidget
{
public:
    enum InputTouchState
    {
        ctInputTouchBegin,
        ctInputTouchEnd,
        ctInputTouchUpdate
    };
    enum InputMouseState
    {empty};

private:
    //friend ctInputHelper;//TriangleWindow;
   // QVector<QMouseEvent *> m_mouseEvent;
    QVector<QKeyEvent *> m_keyEvent;
   // QVector<QTouchEvent *> m_touchEvent;
    QMouseEvent * m_lastMouseEvent;
    QTouchEvent * m_lastTouchEvent;
    InputTouchState m_lastTouchState;
    ctInputEvent m_eventsPool[255];
    quint64 m_iterationStamp;
    ctInputHelper m_helper;
    ctWindow * m_window;

public:
    explicit ctInput(ctWindow * t_window = 0, QWidget * parent = 0);
    ~ctInput();

    QVector<QMouseEvent *> GetMouseEvent();
    QVector<QKeyEvent *> GetKeyEvent();
    //QVector<QTouchEvent *> GetTouchEvent();
    QTouchEvent* GetTouchEvent() const;
    InputTouchState GetTouchState();
    QMouseEvent * GetMouseEvent() const;

    int GetIndexOfDeadEvent();

    void Update();

    void PostUpdate(); //cleaning buffers

    bool event(QEvent *event);

    void AddEvent(ctInputEvent);

    QVector<ctInputEvent> GetEvents(unsigned int t_flags);

    ctInputHelper GetInputHelper() const;

    void SetWindow(ctWindow*);
    ctWindow* GetWindow() const;

};

#endif // CTINPUT_H
