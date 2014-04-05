#ifndef CTINPUTHELPER_H
#define CTINPUTHELPER_H

#include <QMouseEvent>
#include <QVector>
#include <QList>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QWidget>

//#include "ctInput.h"

class ctInput;
class ctInputHelper
{
public:
    enum mouseButtons
    {
        MB_LEFT         = 0,
        MB_MIDDLE       = 1,
       // MB_RIGHTt        = 2
    };
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
    QList<QTouchEvent::TouchPoint> m_touches;
    ctInput * m_input;
    bool GetMouseButtonState(int t_button, int t_state) const;
public:
    ctInputHelper(ctInput * t_input);
    void ProcessingEvent(QEvent *event);
    void Update();
    //---------------------------------------
    bool IsMouseLeftButtonPressNhold() const;
    bool IsMouseLeftButtonPush() const;
    bool IsMouseLeftButtonRelease() const;
    bool IsMouseLeftButtonNoneActive() const;
    //---------------------------------------
    bool IsMouseRightButtonPressNhold() const;
    bool IsMouseRightButtonPush() const;
    bool IsMouseRightButtonRelease() const;
    bool IsMouseRightButtonNoneActive() const;
    //---------------------------------------
    QList<QTouchEvent::TouchPoint> GetTouches() const;

    QVector2D GetMousePos2D() const;
    QVector3D GetMousePos3D();// const;
};

#endif // CTINPUTHELPER_H
