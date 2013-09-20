#ifndef LIGHT_TEST_H
#define LIGHT_TEST_H
#include <QVector3D>
#include <QVector4D>
// параметры точеченого источника освещения
struct PointLight
{
    QVector4D position;
    QVector4D ambient;
    QVector4D diffuse;
    QVector4D specular;
    QVector3D attenuation;
};

// параметры материала
struct Material
{
    unsigned int texture;

    QVector4D  ambient;
    QVector4D  diffuse;
    QVector4D  specular;
    QVector4D  emission;
    float shininess;
};
#endif // LIGHT_TEST_H
