#include "ctEntity.h"

ctEntity::ctEntity()
{
    m_name = QString("NewEntity");
    m_uuid = QUuid::createUuid();
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
