#ifndef CTTRANSFORM_H
#define CTTRANSFORM_H

#include <QVector>
#include <QMatrix3x3>
#include <QString>
#include <QUuid>
#include <QVector3D>

#include "ctMatrix4.h"

class ctEntity;
class ctObject;

class ctTransform
{
private:
    QVector<ctTransform * > * m_childrens;
    ctTransform * m_parent;
    ctMatrix4 m_localTransform;
    ctEntity * m_entity;
    //TODO: move to ctEntity;
    //QString m_name;
    //QUuid m_uuid;
    //-----------------------
public:
    ctTransform();
    ctTransform(ctEntity * t_entity);
    ~ctTransform();

    void SetDefault();

    ctTransform * GetChild(int);
    ctTransform * GetChild(QUuid);
    ctTransform * GetChild(QString);
    void AddChild(ctTransform *);
    void DeleteChild(int);
    void DeleteChild(QUuid);
    void DeleteChild(QString);

    //QUuid GetUuid() const;
    //QString GetName() const;
    ctMatrix4 GetLocalTransformMatrix() const;
    ctMatrix4 GetGlobalTransformMatrix() const;

    //TODO: Need retation, move & scale methods!!!

    void Move(QVector3D);
    void Scale(QVector3D);
    void RotateByX(float);
    void RotateByY(float);
    void RotateByZ(float);

    ctEntity * GetEntity();
};

#endif // CTTRANSFORM_H
