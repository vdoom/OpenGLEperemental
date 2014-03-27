#ifndef CTTEXTURE_H
#define CTTEXTURE_H

#include <QtGui/QOpenGLFunctions>
#include "ctAsset.h"

class ctTexture : public ctAsset
{
private:
    int m_width, m_height;
    GLuint m_textureIndex;
    QOpenGLContext * m_OpenGLcontext;
    void LoadImageToTexture(const char *t_fileName, const char *t_fileFormat = 0);
public:
    ctTexture();
    ctTexture(const char * t_fileName, const char * t_fileFormat = 0);
    virtual ~ctTexture();
    virtual void Load();

    GLuint GetTextureIndex() const;
    int GetWidth() const;
    int GetHeight() const;
};

#endif // CTTEXTURE_H
