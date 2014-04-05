#ifndef CTASSET_H
#define CTASSET_H

class ctAsset
{
public:
    enum AssetType
    {
        AT_TEXTURE,
        AT_SOUND
    };
protected:
    int m_type;
public:
    ctAsset();
    virtual ~ctAsset();

    virtual void Load() = 0;
    int GetType();
};

#endif // CTASSET_H
