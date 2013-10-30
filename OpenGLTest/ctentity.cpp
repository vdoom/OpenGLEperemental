#include "ctEntity.h"

ctEntity::ctEntity()
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
