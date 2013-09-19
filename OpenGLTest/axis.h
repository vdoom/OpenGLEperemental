#ifndef AXIS_H
#define AXIS_H

#include <QObject>
#include <QtGui/QOpenGLFunctions>
#include <QVector3D>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include "shadermanager.h"

class Axis// : public QObject
{
    //Q_OBJECT
private:
    QVector3D m_axisVector;
    QVector3D m_axisColor;
    GLfloat *colorsArray;
    GLfloat *coordsArray;
    QMatrix3x3 m_matrix;
    ShaderManager * m_shaderManager;

    GLuint posAtribLoc;
    GLuint colorAtribLoc;
    GLuint matrixUniform;

    void SetUpCoords(QVector3D t_axisVector);
    void SetUpColor(QVector3D t_axisColor);
public:
    explicit Axis(QVector3D t_axisVector, QVector3D t_axisColor, ShaderManager * t_shaderManager);
    ~Axis();
    void Draw(QMatrix4x4);
    
//signals:
    
//public slots:
    
};

#endif // AXIS_H
