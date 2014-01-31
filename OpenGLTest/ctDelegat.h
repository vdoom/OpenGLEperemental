#ifndef CTDELEGAT_H
#define CTDELEGAT_H

class ctDelegat
{
public:
    ctDelegat();
    void (*delegat)();
    void Call();
};

#endif // CTDELEGAT_H
