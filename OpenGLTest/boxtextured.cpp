#include "boxtextured.h"
#include <QDebug>
#include "common.h"
#include <QFile>

BoxTextured::BoxTextured(ShaderManager * t_shaderManager)
{
    m_shaderManager = t_shaderManager;
}

void BoxTextured::Draw(QMatrix4x4 t_projectionMatrix)
{
    // количество вершин куба
    const uint32_t cubeVerticesCount = 24;

    // описание геометрии куба для всех его сторон
    // координаты вершин куба
    const float s = 1.0f; // половина размера куба
    const float cubePositions[cubeVerticesCount][3] = {
            {-s, s, s}, { s, s, s}, { s,-s, s}, {-s,-s, s}, // front
            { s, s,-s}, {-s, s,-s}, {-s,-s,-s}, { s,-s,-s}, // back
            {-s, s,-s}, { s, s,-s}, { s, s, s}, {-s, s, s}, // top
            { s,-s,-s}, {-s,-s,-s}, {-s,-s, s}, { s,-s, s}, // bottom
            {-s, s,-s}, {-s, s, s}, {-s,-s, s}, {-s,-s,-s}, // left
            { s, s, s}, { s, s,-s}, { s,-s,-s}, { s,-s, s}  // right
    };

    // текстурные координаты куба
    const float cubeTexcoords[cubeVerticesCount][2] = {
            {0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // front
            {0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // back
            {0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // top
            {0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // bottom
            {0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}, // left
            {0.0f,1.0f}, {1.0f,1.0f}, {1.0f,0.0f}, {0.0f,0.0f}  // right
    };

    // количество индексов куба
    const uint32_t cubeIndicesCount = 36;

    // индексы вершин куба в порядке поротив часовой стрелки
    const uint32_t cubeIndices[cubeIndicesCount] = {
             0, 3, 1,  1, 3, 2, // front
             4, 7, 5,  5, 7, 6, // back
             8,11, 9,  9,11,10, // top
            12,15,13, 13,15,14, // bottom
            16,19,17, 17,19,18, // left
            20,23,21, 21,23,22  // right
    };

//    GLfloat colors[] = {
//        1.0f, 0.3f, 0.3f,
//        1.0f, 0.3f, 0.3f,
//        0.3f, 1.0f, 0.3f,
//        0.3f, 1.0f, 0.3f,
//        0.3f, 0.3f, 1.0f,
//        0.3f, 0.3f, 1.0f
//    };

    m_currentShaderProgram->bind();
    m_currentShaderProgram->setUniformValue(textureLocation, 0);
    m_currentShaderProgram->setUniformValue(matrixUniform, t_projectionMatrix);

    glVertexAttribPointer(posAtribLoc, 3, GL_FLOAT, GL_FALSE, 0, cubePositions);
    glVertexAttribPointer(colorAtribLoc, 2, GL_FLOAT, GL_FALSE, 0, cubeTexcoords);

    glEnableVertexAttribArray(posAtribLoc);
    glEnableVertexAttribArray(colorAtribLoc);

    glDrawElements(GL_TRIANGLES, cubeIndicesCount, GL_UNSIGNED_INT, cubeIndices);

    glDisableVertexAttribArray(colorAtribLoc);
    glDisableVertexAttribArray(posAtribLoc);

    m_currentShaderProgram->release();

}

void BoxTextured::InitShaderProgram()
{
    m_currentShaderProgram = m_shaderManager->SetUpShaderProgram(1, 1);
    posAtribLoc = m_currentShaderProgram->attributeLocation("position");
    colorAtribLoc = m_currentShaderProgram->attributeLocation("texcoord");
    matrixUniform = m_currentShaderProgram->uniformLocation("modelViewProjectionMatrix");
    textureLocation = m_currentShaderProgram->uniformLocation("colorTexture");
}

GLuint BoxTextured::TextureCreateFromTGA(const char *fileName)
{
        //ASSERT(fileName);

        TGAHeader *header;
        uint8_t   *buffer;
        uint32_t  size;
        GLint     format, internalFormat;
        GLuint    texture;

        // попытаемся загрузить изображение из файла
        //if (!LoadFile(fileName, true, &buffer, &size))
        //        return 0;
        QString fileNametmp(fileName);
        QFile * m_file = new QFile(fileNametmp);
        size = m_file->size();
        m_file->open(QFile::ReadOnly);
        m_file->seek(0);
        QByteArray tmp = m_file->readAll();
        buffer = new uint8_t[size]; //(uint8_t*)tmp.data();

        for(int i = 0; i< size; ++i)
        {
            buffer[i] = (uint8_t)tmp.data()[i];
        }
        // если размер файла заведомо меньше заголовка TGA
        if (size <= sizeof(TGAHeader))
        {
            qDebug()<<"Too small file '%s'\n";
                //LOG_ERROR("Too small file '%s'\n", fileName);
                delete[] buffer;
                return 0;
        }

        header = (TGAHeader*)buffer;

        // проверим формат TGA-файла - несжатое RGB или RGBA изображение
        if (header->datatype != 2 || (header->bitperpel != 24 && header->bitperpel != 32))
        {
            qDebug()<<"Wrong TGA format '%s'\n";
                //LOG_ERROR("Wrong TGA format '%s'\n", fileName);
                delete[] buffer;
                return 0;
        }

        // получим формат текстуры
        format = (header->bitperpel == 24 ? GL_BGR : GL_BGRA);
        internalFormat = (format == GL_BGR ? GL_RGB8 : GL_RGBA8);

        // запросим у OpenGL свободный индекс текстуры
        glGenTextures(1, &texture);

        // сделаем текстуру активной
        glBindTexture(GL_TEXTURE_2D, texture);

        // установим параметры фильтрации текстуры - линейная фильтрация
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // установим параметры "оборачивания" текстуры - отсутствие оборачивания
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // загрузим данные о цвете в текущую автивную текстуру
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, header->width, header->height, 0, format,
                GL_UNSIGNED_BYTE, (const GLvoid*)(buffer + sizeof(TGAHeader) + header->idlength));

        // после загрузки в текстуру данные о цвете в памяти нам больше не нужны
        delete[] buffer;

        // проверим на наличие ошибок
        //OPENGL_CHECK_FOR_ERRORS();

        return texture;
}

/*GLuint BoxTextured::TextureCreateFromTGA(const char *fileName = 0)
{
    GLint     format, internalFormat;
    GLuint    texture;

    // получим формат текстуры
    format = 0x80E0;
    internalFormat = 0x8051;

    uint8_t buffer[] = {255,255,255,255};
    // запросим у OpenGL свободный индекс текстуры
    glGenTextures(1, &texture);

    // сделаем текстуру активной
    glBindTexture(GL_TEXTURE_2D, texture);

    // установим параметры фильтрации текстуры - линейная фильтрация
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // установим параметры "оборачивания" текстуры - отсутствие оборачивания
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // загрузим данные о цвете в текущую автивную текстуру
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, format,
            GL_UNSIGNED_BYTE, (const GLvoid*)(buffer));

    // после загрузки в текстуру данные о цвете в памяти нам больше не нужны
    //delete[] buffer;

    // проверим на наличие ошибок
    //OPENGL_CHECK_FOR_ERRORS();

    return texture;
        return texture;
}*/

void BoxTextured::LoadTexture(const char * t_textureFileName)
{
    // переменная для хранения индекса текстуры
    GLuint colorTexture = 0;

    // создадим и загрузим текстуру
    colorTexture = TextureCreateFromTGA(t_textureFileName);

    // если не получилось загрузить текстуру
    if (!colorTexture)
            return;

    // делаем активным текстурный юнит 0
    glActiveTexture(GL_TEXTURE0);

    // назначаем текстуру на активный текстурный юнит
    glBindTexture(GL_TEXTURE_2D, colorTexture);

    // получим индекс текстуры из шейдерной программы
   //glGetUniformLocation(shaderProgram, "colorTexture");

    // укажем, что текстура привязана к текстурному юниту 0
    //if (textureLocation != -1)
      //  m_shaderManager->GetCurrentShaderProgram()->setUniformValue(textureLocation, 0);
            //glUniform1i(textureLocation , 0);
}
