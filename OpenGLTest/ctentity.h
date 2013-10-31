#ifndef CTENTITY_H
#define CTENTITY_H

#include <QString>
#include <QUuid>

class ctEntity
{
private:
    bool m_isFreeze;
    bool m_isVisible;
    bool m_isFreezable;
    QString m_name;
    QUuid m_uuid;
protected:

public:
    ctEntity();
    virtual ~ctEntity(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Init() = 0;
    virtual void Hide();
    virtual void Show();
    virtual void Freeze();
    virtual void Unfreeze();
    //---NEW-EXPERIMETAL-FUNCTIONAL---
    QString GetName() const;
    void SetName(QString t_newName);
    QUuid GetUuid() const;
    bool IsFreezable() const;
    bool IsFreezed() const;
    bool IsVisible() const;
    QString GetTypeName() const;
    //--------------------------------
};

#endif // CTENTITY_H
