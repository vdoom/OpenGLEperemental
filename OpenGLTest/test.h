#ifndef TEST_H
#define TEST_H

#include "QVector3D"

template<typename T> class Vector2D
{
private:
    T m_x;
    T m_y;
public:
    Vector2D(T t_x, T t_y)
    {
        m_x = t_x;
        m_y = t_y;
    }
    ~Vector2D()
    {}

    void SetX(const T& t_x)
    {m_x = t_x;}

    void SetY(const T& t_y)
    {m_y = t_y;}

    T GetX() const
    {return m_x;}

    T GetY() const
    {return m_y;}
};

template<typename T> class ctVector3D
{
private:
    T* t;
//    T m_x;
//    T m_y;
//    T m_z;
public:
    ctVector3D()
    {
        t = new T[3];
        t[0] = (T)0;
        t[1] = (T)0;
        t[2] = (T)0;
    }
    ctVector3D(T t_x, T t_y, T t_z)
    {
        t = new T[3];
        t[0] = t_x;
        t[1] = t_y;
        t[2] = t_z;
    }

    ~ctVector3D()
    {}

    void SetX(const T& t_x)
    {t[0] = t_x;}

    void SetY(const T& t_y)
    {t[1] = t_y;}

    void SetZ(const T& t_z)
    {t[2] = t_z;}

    T GetX() const
    {return t[0];}

    T GetY() const
    {return t[1];}

    T GetZ() const
    {return t[2];}

    ctVector3D & operator = (QVector3D t_vector)
    {
        t[0] = (T)t_vector.x();
        t[1] = (T)t_vector.y();
        t[2] = (T)t_vector.z();
    }

    T* GetData()
    {
        return t;
    }

    operator float()
    {
        return *t;
    }
};

typedef ctVector3D<float>  ctVector3Df;
typedef ctVector3D<double> ctVector3Dd;
typedef ctVector3D<int>    ctVector3Di;
#endif // TEST_H
