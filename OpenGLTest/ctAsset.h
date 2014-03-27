#ifndef CTASSET_H
#define CTASSET_H

class ctAsset
{
public:
    ctAsset();
    virtual ~ctAsset();

    virtual void Load() = 0;
};

#endif // CTASSET_H
