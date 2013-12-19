#ifndef CTINPUT_H
#define CTINPUT_H

#include <QMouseEvent>
#include <QVector>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QWidget>

//class TriangleWindow;
#include "ctInputEvent.h"

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
    //friend TriangleWindow;
   // QVector<QMouseEvent *> m_mouseEvent;
    QVector<QKeyEvent *> m_keyEvent;
   // QVector<QTouchEvent *> m_touchEvent;
    QMouseEvent * m_lastMouseEvent;
    QTouchEvent * m_lastTouchEvent;
    InputTouchState m_lastTouchState;
    ctInputEvent m_eventsPool[255];
    quint64 m_iterationStamp;

public:
    explicit ctInput(QWidget * parent = 0);
    ~ctInput();

    QVector<QMouseEvent *> GetMouseEvent();
    QVector<QKeyEvent *> GetKeyEvent();
    //QVector<QTouchEvent *> GetTouchEvent();
    QTouchEvent* GetTouchEvent() const;
    InputTouchState GetTouchState();
    QMouseEvent * GetMouseEvent() const;

    //GetIndexOfDeadIndex();

    void Update();

    void PostUpdate(); //cleaning buffers

    bool event(QEvent *event);
};

#endif // CTINPUT_H
