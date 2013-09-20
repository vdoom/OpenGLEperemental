#ifndef BOXTEXTURED_H
#define BOXTEXTURED_H
#include <QObject>
#include <QtGui/QOpenGLFunctions>
#include <QVector3D>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include "shadermanager.h"
#include "common.h"

class BoxTextured
{
private:
    struct TGAHeader
    {
            uint8_t  idlength;
            uint8_t  colormap;
            uint8_t  datatype;
            uint8_t  colormapinfo[5];
            uint16_t xorigin;
            uint16_t yorigin;
            uint16_t width;
            uint16_t height;
            uint8_t  bitperpel;
            uint8_t  description;
    };
    GLuint textureLocation = -1;
    bool LoadFile(const char *fileName, bool binary, uint8_t **buffer, quint32 *size)
    {
        //ASSERT(fileName);
        //ASSERT(buffer);
        //ASSERT(size);

        FILE     *input;
        uint32_t fileSize, readed;

        const char mode[] = {'r', binary ? 'b' : 't', '\0'};

        if ((input = fopen(fileName, mode)) == NULL)
        {
            qDebug()<<"Opening file '%s'\n";
            //LOG_ERROR("Opening file '%s'\n", fileName);
            return false;
        }

        fseek(input, 0, SEEK_END);
        fileSize = (uint32_t)ftell(input);
        rewind(input);

        if (fileSize == 0)
        {
            qDebug()<<"Empty file '%s'\n";
            //LOG_ERROR("Empty file '%s'\n", fileName);
            fclose(input);
            return false;
        }

        *buffer = new uint8_t[fileSize];
        //ASSERT(*buffer);

        readed = fread(*buffer, 1, fileSize, input);

        fclose(input);

        if (readed != fileSize)
        {
            qDebug()<<"Reading file '%s'\n";
            //LOG_ERROR("Reading file '%s'\n", fileName);
            delete[] *buffer;
            return false;
        }

        *size = fileSize;

        return true;
    }

    // функция загрузки изображения из файла TGA и сздания текстуры
    GLuint TextureCreateFromTGA(const char *fileName);

    GLuint posAtribLoc;
    GLuint colorAtribLoc;
    GLuint matrixUniform;

    ShaderManager * m_shaderManager;
    QOpenGLShaderProgram * m_currentShaderProgram;
public:
    BoxTextured(ShaderManager * t_shaderManager);
    void Draw(QMatrix4x4);
    void InitShaderProgram();
    void LoadTexture(const char * t_textureFileName);
};

#endif // BOXTEXTURED_H
