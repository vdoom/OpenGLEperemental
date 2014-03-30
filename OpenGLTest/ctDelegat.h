#ifndef CTDELEGAT_H
#define CTDELEGAT_H


struct DVoid
{
    void *tmp1;
    void *tmp2;
};

class ctDelegat
{
private:
    void (ctDelegat::*delegat)();
    ctDelegat * caller;
public:
    union
    {
        DVoid tmp;
        void (ctDelegat::*eee) (void);
    } u;
    ctDelegat();
    ctDelegat(void *t_caller, DVoid t_delegat);

    virtual void eee();
    void Call();
    void SetCaller(ctDelegat * t_caller);
    void SetDelegat(void (*t_del) (void));
};
typedef void (ctDelegat::*eee) (void);


#endif // CTDELEGAT_H
