#ifndef CTOBJECT_H
#define CTOBJECT_H

#include "ctTransform.h"
#include <QGLContext>
#include "ctEntity.h"

class ctShaderManager;
class ctScene;

class ctObject : public ctEntity
{
private:
    QGLContext * m_OpenGLContext;
    bool m_isVisible;
protected:
    ctTransform * m_transform;
    ctMatrix4 m_projectionMatrix;
    ctScene * m_scene;
    ctShaderManager * m_shaderManager;
    virtual void SetDefault(ctShaderManager *, ctScene *, QGLContext *);
public:
    ctObject();
    explicit ctObject(ctShaderManager *);
    ctObject(ctShaderManager *, ctScene *);
    ctObject(ctShaderManager *, ctScene *, QGLContext *);
    virtual ~ctObject();

    //----Override-----
    virtual void Update(){}//=0;
    virtual void Draw(){}//=0;
    virtual void Init(){}//=0;
    virtual void Freeze();
    virtual void Unfreeze();
    virtual ctEntity* Clone();

    virtual void Hide();
    virtual void Show();
    //-----------------

    bool IsVisible();



    ctTransform * GetTransform();// const;
    ctMatrix4 GetProjectionMatrix();// const;
    void SetProjectionMatrix(ctMatrix4 & t_projMat);
    void SetProjectionMatrix(QMatrix4x4 & t_projMat);

    void SetScene(ctScene* t_scene);
    ctScene * GetScene() const;

    void SetShaderManager(ctShaderManager* t_shaderManager);
    ctShaderManager * GetShaderManager() const;

    QGLContext * GetOpenGLContext() const;
    void SetOpenGLContext(const QGLContext * t_context);
};

#endif // CTOBJECT_H
