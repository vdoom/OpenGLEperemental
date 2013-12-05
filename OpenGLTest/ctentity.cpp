#include "ctEntity.h"
#include <typeinfo>
using namespace std;

ctEntity::ctEntity() : m_isInitialized(false), m_isLoaded(false)
{
    m_name = QString("NewEntity");
    m_uuid = QUuid::createUuid();
    m_isFreeze = false;
}

QString ctEntity::GetName() const
{
    return m_name;
}

QUuid ctEntity::GetUuid() const
{
    return m_uuid;
}

bool ctEntity::IsFreezable() const
{
    return m_isFreezable;
}

bool ctEntity::IsFreezed() const
{
    return m_isFreeze;
}

void ctEntity::Freeze()
{
    m_isFreeze = true;
}

void ctEntity::Unfreeze()
{
    m_isFreeze = false;
}

void ctEntity::SetName(QString t_newName)
{
    m_name = t_newName;
}

void ctEntity::Show()
{
    m_isVisible = true;
}

void ctEntity::Hide()
{
    m_isVisible = false;
}

bool ctEntity::IsVisible() const
{
    return m_isVisible;
}

QString ctEntity::GetTypeName() const
{
    QString tmp(typeid(*this).name());
    return tmp;
}

bool ctEntity::IsInitialized() const
{
    return m_isInitialized;
}

bool ctEntity::IsLoaded() const
{
    return m_isLoaded;
}

ctEntity* ctEntity::Clone()
{
    ctEntity* tmpEntity = new ctEntity();
    tmpEntity->SetName(m_name + QString("_clone"));
    return this;
}
