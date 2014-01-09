#ifndef CTINPUTHELPER_H
#define CTINPUTHELPER_H

#include <QMouseEvent>
#include <QVector>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QWidget>

class ctInputHelper
{
public:
    enum mouseButtonState
    {
        MBS_NONE         = 0,
        MBS_PUSH         = 1,
        MBS_PRESS_N_HOLD = 2,
        MBS_RELEASE      = 3
    };
private:
    int m_mouseButtons[3];
    QVector2D m_mousePos;
public:
    ctInputHelper();
    void ProcessingEvent(QEvent *event);
    void Update();
    bool IsMouseLeftButtonPressNhold() const;
    bool IsMouseLeftButtonPush() const;
    bool IsMouseLeftButtonRelease() const;
    bool IsMouseLeftButtonNoneActive() const;
    QVector2D GetMousePos2D() const;
    QVector3D GetMousePos3D();// const;
};

#endif // CTINPUTHELPER_H
