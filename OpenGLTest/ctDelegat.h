#ifndef CTDELEGAT_H
#define CTDELEGAT_H



class ctDelegat
{
private:
    void (ctDelegat::*delegat)();
    ctDelegat * caller;
public:
    ctDelegat();
    ctDelegat(void *t_caller, void (ctDelegat::*eee)());

    virtual void eee();
    void Call();
    void SetCaller(ctDelegat * t_caller);
    void SetDelegat(void (*t_del) (void));
};
typedef void (ctDelegat::*eee) (void);


#endif // CTDELEGAT_H
