#ifndef PLANE_H
#define PLANE_H
#include <QVector3D>
#include <QMatrix4x4>
#include "shadermanager.h"
class Plane
{
private:
    ShaderManager * m_shaderManager;
    QVector3D m_AA;
    QVector3D m_BB;
    PlaneType m_currentType;
public:
    enum PlaneType
    {
        Colored,
        Textured
    }

    Plane(ShaderManager t_shaderManager, QVector3D t_AA, QVector3D t_BB, PlaneType t_type);
    ~Plane();

    void SetTexture(const char* t_fileName);
    void SetColor(QVector4D t_color);
    void Draw(QMatrix4x4);
};

#endif // PLANE_H
