#ifndef HCIRCLES_H
#define HCIRCLES_H

#include <QVector>
#include "ctPlane.h"

class hCircles : public ctObject
{
private:
    QVector<ctPlane*> m_circles;
public:
    hCircles();
    explicit hCircles(ctShaderManager *);
    hCircles(ctShaderManager *, ctScene *);
    hCircles(ctShaderManager *, ctScene *, QOpenGLContext *);

    virtual ~hCircles();

    virtual void Init();
    virtual void Update();
    virtual void Draw();

    static QString GetCircleResPath(int t_color, int t_size)
    {
        QString mainPath(":/texture/circles/");
        QString color("red");
        switch(t_color)
        {
        case 0:
            color = QString("red");
            break;
        case 1:
            color = QString("blue");
            break;
        case 2:
            color = QString("yellow");
            break;
        case 3:
            color = QString("green");
            break;
        default:
            color = QString("red");
            break;
        }
        mainPath += color;
        if(t_size < 1 && t_size > 4) t_size = 1;
        mainPath += QString::number(t_size);
        mainPath += QString(".png");
		return mainPath;
    }
};

#endif // HCIRCLES_H
