#ifndef CTSCENE_H
#define CTSCENE_H

#include <QVector>

#include "ctObject.h"

class ctShaderManager;

class ctScene : public ctObject
{
private:
    //TODO: make m_scene as privat in this class
protected:
    QVector<ctObject*>* m_objects;
    QVector<ctEntity*>* m_components;
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
public:
    ctScene();
    explicit ctScene(ctShaderManager *);
    ctScene(ctShaderManager *, QOpenGLContext *);
    virtual ~ctScene();

    void AddObject(ctObject*);
    void AddComponnent(ctEntity*);
    //TODO: ADD FUNCTIONS FOR DELETING OBJECTS !!!

    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual void Freeze();
    virtual void Unfreeze();

    ctObject* GetObjectByUUID(QUuid t_uuid);
    ctEntity* GetComponentByUUID(QUuid t_uuid);

    QVector<ctObject*> GetObjectsByName(QString t_name);
    QVector<ctEntity*> GetComponentByName(QString t_name);
    //TODO: NEED TEST!!!
    template<class T> QVector<T*> GetObjectsByType();// GetObjectByType<ctPlane>();
    template<class T> QVector<T*> GetComponnetsByType();
};

#endif // CTSCENE_H
