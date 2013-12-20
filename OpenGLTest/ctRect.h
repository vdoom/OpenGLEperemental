#ifndef CTRECT_H
#define CTRECT_H

#include "QVector3D"
#include "ctMatrix4.h"

class ctRect
{
private:
    QVector3D m_topLeft;
    QVector3D m_topRigth;
    QVector3D m_bottomLeft;
    QVector3D m_bottomRight;
protected:
public:
    ctRect();
    ctRect(QVector3D t_topLeft, QVector3D t_topRight, QVector3D t_bottomLeft, QVector3D t_bottomRight);

    ~ctRect();

    void SetUpRect(QVector3D t_topLeft, QVector3D t_topRight, QVector3D t_bottomLeft, QVector3D t_bottomRight);

    void SetTopLeft(const QVector3D& t_topLeft);
    void SetTopRight(const QVector3D& t_topRight);
    void SetBottomLeft(const QVector3D& t_bottomLeft);
    void SetBottomRight(const QVector3D& t_bottomRight);

    QVector3D GetTopLeft() const;
    QVector3D GetTopRight() const;
    QVector3D GetBottomLeft() const;
    QVector3D GetBottomRight() const;

    float GetMaxX() const;
    float GetMinX() const;
    float GetMaxY() const;
    float GetMinY() const;

    ctRect operator=( const ctRect & t_rect)
    {
        SetTopLeft(t_rect.GetTopLeft());
        SetTopRight(t_rect.GetTopRight());
        SetBottomLeft(t_rect.GetBottomLeft());
        SetBottomRight(t_rect.GetBottomRight());
    }

//    ctRect operator * (const QMatrix4x4& t_mat, const ctRect& t_rect)
//    {
//        return ctRect((t_mat * t_rect.GetTopLeft()), (t_mat * t_rect.GetTopRight()), (t_mat * t_rect.GetBottomLeft()), (t_mat * t_rect.GetBottomRight()));
//    }

//    ctRect operator * (const ctMatrix4& t_mat, const ctRect& t_rect)
//    {
//        return ctRect((t_mat.GetMatrix() * t_rect.GetTopLeft()), (t_mat.GetMatrix() * t_rect.GetTopRight()), (t_mat.GetMatrix() * t_rect.GetBottomLeft()), (t_mat.GetMatrix() * t_rect.GetBottomRight()));
//    }
};

ctRect operator * (const ctMatrix4& t_mat, const ctRect& t_rect);
ctRect operator * (const QMatrix4x4& t_mat, const ctRect& t_rect);

#endif // CTRECT_H
