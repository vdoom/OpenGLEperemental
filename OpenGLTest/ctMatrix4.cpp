#include "ctMatrix4.h"
#include <math.h>
#include <QDebug>
ctMatrix4::ctMatrix4()
{
    m_matrix.setToIdentity();
}

ctMatrix4::ctMatrix4(QMatrix4x4 t_matrix)
{SetMatrix(t_matrix);}

QMatrix4x4 ctMatrix4::GetMatrix() const
{return m_matrix;}

void ctMatrix4::Translate(QVector3D t_pos)
{
    QMatrix4x4 tmp;
    tmp.setToIdentity();

    tmp(0, 3) = t_pos.x();
    tmp(1, 3) = t_pos.y();
    tmp(2, 3) = t_pos.z();
    m_matrix.translate(t_pos.x(),t_pos.y(),t_pos.z());
    //m_matrix = tmp * m_matrix;
    qDebug() << m_matrix(0, 3);
}

void ctMatrix4::Scale(QVector3D t_scl)
{
    QMatrix4x4 tmp;
    tmp.setToIdentity();

    tmp(0, 0) = t_scl.x();
    tmp(1, 1) = t_scl.y();
    tmp(2, 2) = t_scl.z();
    m_matrix *= tmp;
}

void ctMatrix4::RotateX(float t_xangle)
{
    QMatrix4x4 tmp;
    tmp.setToIdentity();

    tmp(1,1) = cos(t_xangle);
    tmp(1,2) = sin(t_xangle);
    tmp(2,1) = -sin(t_xangle);
    tmp(2,2) = cos(t_xangle);

    m_matrix *= tmp;
}

void ctMatrix4::RotateY(float t_yangle)
{
    QMatrix4x4 tmp;
    tmp.setToIdentity();

    tmp(0,0) = cos(t_yangle);
    tmp(0,2) = -sin(t_yangle);
    tmp(2,0) = sin(t_yangle);
    tmp(2,2) = cos(t_yangle);

    m_matrix *= tmp;
}

void ctMatrix4::RotateZ(float t_zangle)
{
    QMatrix4x4 tmp;
    tmp.setToIdentity();

    tmp(0,0) = cos(t_zangle);
    tmp(0,1) = sin(t_zangle);
    tmp(1,0) = -sin(t_zangle);
    tmp(1,1) = cos(t_zangle);

    m_matrix *= tmp;
}

void ctMatrix4::SetMatrix(QMatrix4x4 t_matrix)
{
    m_matrix = t_matrix;
}

void ctMatrix4::Multiply(QMatrix4x4 t_matrix)
{
    m_matrix *= t_matrix;
}

void ctMatrix4::Multiply(ctMatrix4 t_matrix)
{
    Multiply(t_matrix.GetMatrix());
}
