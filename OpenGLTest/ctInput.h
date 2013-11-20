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
private:
    //friend TriangleWindow;
    QVector<QMouseEvent *> m_mouseEvent;
    QVector<QKeyEvent *> m_keyEvent;
    QVector<QTouchEvent *> m_touchEvent;
public:
    explicit ctInput(QWidget * parent = 0);
    ~ctInput();

    QVector<QMouseEvent *> GetMouseEvent();
    QVector<QKeyEvent *> GetKeyEvent();
    QVector<QTouchEvent *> GetTouchEvent();

    void Update();

    void PostUpdate(); //cleaning buffers

    bool event(QEvent *event);
};

#endif // CTINPUT_H
