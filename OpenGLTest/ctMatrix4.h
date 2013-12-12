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
    explicit ctMatrix4(QMatrix4x4);
    void Translate(QVector3D);
    void Scale(QVector3D);
    void RotateX(float);
    void RotateY(float);
    void RotateZ(float);

    void Multiply(const QMatrix4x4&);
    void Multiply(const ctMatrix4&);

    QMatrix4x4 GetMatrix() const;
    void SetMatrix(const QMatrix4x4&);

    ctMatrix4 operator *(ctMatrix4 & t_mat)
    {
        ctMatrix4 tmp(*this);
        tmp.Multiply(t_mat);
        return tmp;
    }

    ctMatrix4 operator *= (ctMatrix4 & t_mat)
    {
        this->Multiply(t_mat);
        return *this;
    }

    //ctMatrix4& operator = (ctMatrix4 & t_mat);//const;
//    ctMatrix4& operator = ( const ctMatrix4 & t_mat)
//    {
//        //m_matrix = const_cast<QMatrix4x4*>(&m_matrix);
//        m_matrix.setToIdentity();
//        m_matrix *= t_mat.GetMatrix();
//        return *this;
//    }
        ctMatrix4 operator=( const ctMatrix4 & t_mat)
        {
            //m_matrix = const_cast<QMatrix4x4*>(&m_matrix);
            m_matrix.setToIdentity();
            m_matrix *= t_mat.GetMatrix();
            return *this;
        }

//    ctMatrix4& operator = (ctMatrix4 t_mat)
//    {
//        m_matrix.setToIdentity();
//        m_matrix *= t_mat.GetMatrix();
//        return *this;
//    }

//    ctMatrix4& operator = (const ctMatrix4&& t_mat) // move assignment
//    {
//        m_matrix.setToIdentity();
//        m_matrix *= t_mat.GetMatrix();
//        return *this;
//    }

    ctMatrix4 Transpose();
    ctMatrix4 Transposed();
    ctMatrix4 Inverted();//(bool);
//    ctMatrix4 operator= (ctMatrix4 & t_mat)
//    {
//        SetMatrix(t_mat.GetMatrix());
//        return *this;
//    }
};

#endif // CTMATRIX4_H
