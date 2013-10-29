#ifndef CTENTITY_H
#define CTENTITY_H

#include <QString>
#include <QUuid>

class ctEntity
{
protected:
    QString m_name;
    QUuid m_uuid;
    bool m_isFreezable;
public:
    ctEntity();
    virtual ~ctEntity(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Init() = 0;
    virtual void Freeze() = 0;
    virtual void Unfreez() = 0;
    //---NEW-EXPERIMETAL-FUNCTIONAL---
    virtual QString GetTypeName() = 0;
    QString GetName() const;
    QUuid GetUuid() const;
    bool IsFreezable() const;
    //--------------------------------
};

#endif // CTENTITY_H
