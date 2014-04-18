#ifndef CTGLWIDGET_H
#define CTGLWIDGET_H
#include <QGLWidget>

class ctScene;

class ctGLWidget : public QGLWidget
{
    Q_OBJECT
private:
    ctScene* m_scene;
protected:
    virtual void paintGL();
    virtual void initializeGL();
public:
    ctGLWidget(QWidget *parent = 0);
    void SetScene(ctScene*);
    ctScene* GetScene();
};

#endif // CTGLWIDGET_H
