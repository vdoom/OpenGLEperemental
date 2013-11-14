#ifndef TEST_H
#define TEST_H

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

    SetX(const T& t_x)
    {m_x = t_x;}

    SetY(const T& t_y)
    {m_y = t_y;}

    T GetX() const
    {return m_x;}

    T GetY() const
    {return m_y;}
};

#endif // TEST_H
