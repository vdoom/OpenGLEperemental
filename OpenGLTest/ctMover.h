#ifndef CTMOVER_H
#define CTMOVER_H

#include "ctEntity.h"
#include "ctTime.h"
#include "ctTransform.h"
#include "ctFastDelegat.h"

class ctMover : public ctEntity
{
private:
    ctTransform * m_paretnTransform;
    QVector3D m_startPos;
    QVector3D m_endPos;
    QVector3D m_delta;
    float m_elapsed;
    float m_duration;
    float m_currentPos;
    bool m_isCyclic;
    bool m_isWorking;
    ctFastDelegat m_OnFinish;
public:
    ctMover();
    virtual ~ctMover();

    virtual void Update();
    virtual void Draw(){}
    virtual void Init(){}

    void SetUp(QVector3D t_startPos, QVector3D t_endPos, float t_time, bool t_cyclic, ctTransform * t_transform);
    void SetTransform(ctTransform * t_transform);
    void Start();
    void Stop();
    bool IsCyclic();
    void SetCyclic(bool t_isCyclic);
    bool IsWork();

    ctFastDelegat* GetDelegatOnFinish();
    //explicit ctMover(QObject *parent = 0);
};

#endif // CTMOVER_H
