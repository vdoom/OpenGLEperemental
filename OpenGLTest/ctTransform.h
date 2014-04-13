#ifndef CTTRANSFORM_H
#define CTTRANSFORM_H

#include <QVector>
#include <QMatrix3x3>
#include <QString>
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
    ctMatrix4 m_globalTransform;//TODO: steel need refine!!!
    ctEntity * m_entity;

    void UpdateGlobalTransformMatrix();
public:
    ctTransform();
    ctTransform(ctEntity * t_entity);
    ~ctTransform();

    void SetDefault();

    ctTransform * GetChild(int);
    ctTransform * GetChild(QUuid);
    ctTransform * GetChild(QString);
    ctTransform * GetParent() const;
    void AddChild(ctTransform *);
    void DeleteChild(int);
    void DeleteChild(QUuid);
    void DeleteChild(QString);

    ctMatrix4 GetLocalTransformMatrix() const;
    ctMatrix4 GetGlobalTransformMatrix();// const;

    void SetLocalMatrix(const ctMatrix4 & t_matrix);
    void SetLocalMatrix(const QMatrix4x4 & t_matrix);

    void Move(QVector3D);
    void MoveBy(QVector3D);
    void Scale(QVector3D);
    void RotateByX(float);
    void RotateByY(float);
    void RotateByZ(float);

    ctEntity * GetEntity() const;

    bool GetParentsVisibility() const;

    bool IsVisible() const;
    void SetVisible(bool t_visible);

    void SetParent(const ctTransform * t_transform);

    QVector3D GetLocalPos();
    QVector3D GetGlobalPos();
};

#endif // CTTRANSFORM_H
