#ifndef CTSCENE_H
#define CTSCENE_H

#include <QVector>

#include "ctObject.h"

class ctShaderManager;

class ctScene : public ctObject
{
protected:
    QVector<ctObject*>* m_objects;
    QVector<ctEntity*>* m_components;
    ctShaderManager* m_shaderManager;
public:
    ctScene();
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

    void SetShaderManager(ctShaderManager * t_shaderManager);
    ctShaderManager * GetShaderManager() const;
};

#endif // CTSCENE_H
