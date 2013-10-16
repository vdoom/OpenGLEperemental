//#ifndef CTOBJECT_H
//#define CTOBJECT_H

#include "ctTransform.h"
#include "ctentity.h"

class ctObject : public ctEntity
{
private:
protected:
    ctTransform * m_transform;
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

};

//#endif // CTOBJECT_H
