//#ifndef CTOBJECT_H
//#define CTOBJECT_H

#include "ctTransform.h"
#include "ctEntity.h"

class ctShaderManager;
class ctScene;

class ctObject : public ctEntity
{
private:
protected:
    ctTransform * m_transform;
    ctMatrix4 m_projectionMatrix;
    ctScene * m_scene;
    ctShaderManager * m_shaderManager;
public:
    ctObject();
    virtual ~ctObject();

    //----Override-----
    virtual void Update()=0;
    virtual void Draw()=0;
    virtual void Init()=0;
    virtual void Freeze();
    virtual void Unfreeze();
    //-----------------

    ctTransform * GetTransform();// const;
    ctMatrix4 GetProjectionMatrix();// const;
    void SetProjectionMatrix(ctMatrix4 & t_projMat);
    void SetProjectionMatrix(QMatrix4x4 & t_projMat);

    void SetScene(ctScene* t_scene);
    ctScene * GetScene() const;

    void SetShaderManager(ctShaderManager* t_shaderManager);
    ctShaderManager * GetShaderManager() const;
};

//#endif // CTOBJECT_H
