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
    void paintGL();
    void initializeGL();
	void resizeGL(int w, int h){}
public:
    ctGLWidget(ctScene* tt = 0);
    void SetScene(ctScene*);
    ctScene* GetScene();
};

#endif // CTGLWIDGET_H
