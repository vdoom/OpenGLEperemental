#ifndef CTGLWIDGET_H
#define CTGLWIDGET_H
#include <QGLWidget>

class ctGLWidget : public QGLWidget
{
    Q_OBJECT
private:
protected:
    void paintGL ();
    void initializeGL ();
public:
    ctGLWidget(QWidget *parent = 0);
};

#endif // CTGLWIDGET_H
