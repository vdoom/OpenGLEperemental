#ifndef CTSCENE_H
#define CTSCENE_H

#include <QVector>

#include "ctObject.h"

class ctScene : public ctObject
{
protected:
    QVector<ctObject*>* m_objects;
    QVector<ctEntity*>* m_components;
public:
    ctScene();
    virtual ~ctScene();

    void AddObject(ctObject*);
    void AddComponnent(ctEntity*);

    virtual void Update();
    virtual void Draw();
    virtual void Init();
    virtual void Freeze();
    virtual void Unfreeze();
    //TODO: add method for getting objrcts & components by UUID, Name & Types
    ctObject* GetObjectByUUID(QUuid t_uuid);
    ctEntity* GetComponentByUUID(QUuid t_uuid);

    QVector<ctObject*> GetObjectsByName(QString t_name);
    QVector<ctEntity*> GetComponentByName(QString t_name);

    template<class T> QVector< T *> GetObjectsByType();// GetObjectByType<ctPlane>();
    template<class T> QVector< T *> GetComponnetsByType();
};

#endif // CTSCENE_H
