#include "ctDelegat.h"
#include "QDebug"

typedef void (ctDelegat::*eee) (void);

ctDelegat::ctDelegat()
{
}

ctDelegat::ctDelegat(void *t_caller, DVoid t_delegat)
{
    typedef void (ctDelegat::*eee) (void);
    caller = reinterpret_cast<ctDelegat *>(t_caller);
    u.tmp = t_delegat;
    delegat = u.eee;
    //delegat = reinterpret_cast< eee >(t_delegat);
}

void ctDelegat::Call()
{
    (caller->*delegat)();
}

void ctDelegat::SetCaller(ctDelegat *t_caller)
{
    caller = t_caller;
}

void ctDelegat::eee()
{
    qDebug()<<"badRealisation";
}

void ctDelegat::SetDelegat(void (*t_del) (void))
{
    typedef void (ctDelegat::*eee) (void);
    typedef void (*ddd) (void);
    //delegat = reinterpret_cast<eee>(t_del);
}
