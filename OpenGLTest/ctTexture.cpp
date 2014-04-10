#include "ctTexture.h"
#include <QFile>
#include <QImage>
#include <QDebug>

ctTexture::ctTexture() : m_textureIndex(0), m_width(0), m_height(0)
{
}

ctTexture::ctTexture(const char *t_fileName, const char *t_fileFormat) : m_textureIndex(0), m_width(0), m_height(0)
{
    LoadImageToTexture(t_fileName, t_fileFormat);
}

ctTexture::~ctTexture()
{
    qDebug()<<"DestroyTexture";
    if(m_textureIndex > 0)
        glDeleteTextures(1, &m_textureIndex);
}

void ctTexture::Load()
{
}

void ctTexture::LoadImageToTexture(const char *t_fileName, const char *t_fileFormat)
{
    if(m_textureIndex > 0)
        glDeleteTextures(1, &m_textureIndex);

    QString strFileName(t_fileName);

    QFile tmp(strFileName);
    if(tmp.exists())
    {
        qDebug()<<"Texture: "<< strFileName<< " finded";
    }
    else
    {
        qDebug()<<"Errore: "<< strFileName<<" NOT FOUNDED!!!";
        return;
    }
    //QString strFileFormat(fileFormat);
    QImage * image = new QImage(strFileName);//, fileFormat);

    m_width = image->width();
    m_height = image->height();

    qDebug()<<strFileName<<"width: "<< m_width<< " height: "<<m_height;

    //uint8_t   *buffer;
    //uint32_t  size;
    GLint     format, internalFormat;
    GLuint    texture = 0;

    //buffer = new uint8_t[image->byteCount()];


    format = GL_RGBA;//(header->bitperpel == 24 ? GL_RGB : GL_RGBA);
    internalFormat = format;//(format == GL_RGB ? GL_RGB : GL_RGBA);

    glBindTexture(GL_TEXTURE_2D,0);
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image->width(), image->height(), 0, format,
            GL_UNSIGNED_BYTE, (const GLvoid*)(image->bits()));
    glBindTexture(GL_TEXTURE_2D,0);

    //delete[] buffer;

    delete image;

    m_textureIndex = texture;
    qDebug()<<"textureIndex: "<<m_textureIndex;
    //return texture;
}

GLuint ctTexture::GetTextureIndex() const
{
    return m_textureIndex;
}

int ctTexture::GetHeight() const
{
    return m_height;
}

int ctTexture::GetWidth() const
{
    return m_width;
}

void ctTexture::SetDefault()
{
    m_type = ctAsset::AT_TEXTURE;
}
