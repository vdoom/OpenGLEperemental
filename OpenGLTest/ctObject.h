//#ifndef CTOBJECT_H
//#define CTOBJECT_H

#include "ctTransform.h"
#include "ctentity.h"

class ctObject : public ctEntity
{
private:
protected:
    ctTransform m_transform;
    ctMatrix4 m_projectionMatrix;
public:
    ctObject();
    virtual ~ctObject(){}

    //----Override-----
    virtual void Update()=0;
    virtual void Draw()=0;
    virtual void Init()=0;
    virtual void Freeze(){}
    virtual void Unfreez(){}
    //-----------------

    ctTransform GetTransform();// const;
    ctMatrix4 GetProjectionMatrix();// const;
    void SetProjectionMatrix(ctMatrix4 & t_projMat);
    void SetProjectionMatrix(QMatrix4x4 & t_projMat);
};

//#endif // CTOBJECT_H
