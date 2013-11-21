#ifndef CTINPUT_H
#define CTINPUT_H

#include <QMouseEvent>
#include <QVector>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QWidget>

//class TriangleWindow;

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
public:
    explicit ctInput(QWidget * parent = 0);
    ~ctInput();

    QVector<QMouseEvent *> GetMouseEvent();
    QVector<QKeyEvent *> GetKeyEvent();
    //QVector<QTouchEvent *> GetTouchEvent();
    QTouchEvent* GetTouchEvent() const;
    InputTouchState GetTouchState();
    QMouseEvent * GetMouseEvent() const;

    void Update();

    void PostUpdate(); //cleaning buffers

    bool event(QEvent *event);
};

#endif // CTINPUT_H
