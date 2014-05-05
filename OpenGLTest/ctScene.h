#ifndef CTSCENE_H
#define CTSCENE_H

#include <QVector>

#include "ctObject.h"

class ctShaderManager;
class ctWindow;

class ctScene : public ctObject
{
private:
    //TODO: make m_scene as privat in this class
    bool m_dragMode;

protected:
    //TODO: Should delete m_objects container
    QVector<ctObject*>* m_objects;
    ctWindow * m_window;
    //ctGLWidget * m_GLWidget;
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
public:
     QMatrix4x4 matrix;
    ctScene();
    explicit ctScene(ctShaderManager *);
    ctScene(ctShaderManager *, QOpenGLContext *);
    virtual ~ctScene();

    void AddObject(ctObject*);

    virtual void Update();
    virtual void BeginDraw();
    virtual void Draw();
    virtual void EndDraw();
    virtual void Init();
    virtual void Freeze();
    virtual void Unfreeze();

    void SetWindow(ctWindow * t_window);
    ctWindow * GetWindow() const;

//    void DrawText(QPointF t_pos, QString t_str);

    ctObject* GetObjectByUUID(QUuid t_uuid);

    QVector<ctObject*> GetObjectsByName(QString t_name);
    //TODO: NEED TEST!!!
    template<class T> QVector<T*> GetObjectsByType();// GetObjectByType<ctPlane>();

    //--------------------------------------------------

    QOpenGLContext * GetContext();

    bool IsDragMode();
    void SetDragMode(bool t_dragMode);

    QMatrix4x4* GetProjectionMatrix(){return &matrix;}
};

#endif // CTSCENE_H
