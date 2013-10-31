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
    virtual void GetTypeName();
    //TODO: add method for getting objrcts & components by UUID, Name & Types
};

#endif // CTSCENE_H
