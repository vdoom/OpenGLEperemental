#ifndef CTOBJECT_H
#define CTOBJECT_H

#include "ctTransform.h"
//#include <QGLContext>
#include "ctEntity.h"

class ctShaderManager;
class ctScene;
class QOpenGLContext;

class ctObject : public ctEntity
{
private:
    QOpenGLContext * m_OpenGLContext;
    bool m_isVisible;
protected:
    ctTransform * m_transform;
    ctMatrix4 m_projectionMatrix;
    ctScene * m_scene;
    ctShaderManager * m_shaderManager;
    //TDOD: Should delete continer m_components
    QVector<ctEntity*>* m_components;
    virtual void SetDefault(ctShaderManager *, ctScene *, QOpenGLContext *);
public:
    ctObject();
    explicit ctObject(ctShaderManager *);
    ctObject(ctShaderManager *, ctScene *);
    ctObject(ctShaderManager *, ctScene *, QOpenGLContext *);
    virtual ~ctObject();

    //----Override-----
    virtual void Update();
    virtual void Draw(){}//=0;
    virtual void Init(){}//=0;
    virtual void Freeze();
    virtual void Unfreeze();
    virtual ctEntity* Clone();

    virtual void Hide();
    virtual void Show();
    //-----------------

    bool IsVisible();
    //-----------------------------------------
    ctEntity* GetComponentByUUID(QUuid t_uuid);
    QVector<ctEntity*> GetComponentByName(QString t_name);
    template<class T> QVector<T*> GetComponnetsByType();
    void AddComponnent(ctEntity*);
    //-----------------------------------------

    ctTransform * GetTransform();// const;
    ctMatrix4 GetProjectionMatrix();// const;
    virtual void SetProjectionMatrix(ctMatrix4 & t_projMat);
    void SetProjectionMatrix(QMatrix4x4 & t_projMat);

    void SetScene(ctScene* t_scene);
    ctScene * GetScene() const;

    void SetShaderManager(ctShaderManager* t_shaderManager);
    ctShaderManager * GetShaderManager() const;

    QOpenGLContext * GetOpenGLContext() const;
    void SetOpenGLContext(const QOpenGLContext * t_context);
};

#endif // CTOBJECT_H
