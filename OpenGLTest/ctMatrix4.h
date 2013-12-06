#ifndef CTMATRIX4_H
#define CTMATRIX4_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QDebug>

class ctMatrix4
{
private:
    QMatrix4x4 m_matrix;
public:
    ctMatrix4();
    ctMatrix4(QMatrix4x4);
    void Translate(QVector3D);
    void Scale(QVector3D);
    void RotateX(float);
    void RotateY(float);
    void RotateZ(float);

    void Multiply(QMatrix4x4);
    void Multiply(ctMatrix4);

    QMatrix4x4 GetMatrix() const;
    void SetMatrix(QMatrix4x4);

    ctMatrix4 operator *(ctMatrix4 & t_mat)
    {
        ctMatrix4 tmp(*this);
        tmp.Multiply(t_mat);
        return tmp;
    }

//    ctMatrix4 operator= (ctMatrix4 & t_mat)
//    {
//        SetMatrix(t_mat.GetMatrix());
//        return *this;
//    }
};

#endif // CTMATRIX4_H
