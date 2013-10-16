#ifndef CTENTITY_H
#define CTENTITY_H

class ctEntity
{
public:
    ctEntity();
    virtual ~ctEntity(){}

    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Init() = 0;
    virtual void Freeze() = 0;
    virtual void Unfreez() = 0;
};

#endif // CTENTITY_H
