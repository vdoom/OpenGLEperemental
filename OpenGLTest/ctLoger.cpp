#include "ctLoger.h"

ctLoger::ctLoger()
{
    //qDebug()
}

ctLoger::~ctLoger()
{}

void ctLoger::SendLog(QString t_str)
{
    qDebug()<<t_str;
}
