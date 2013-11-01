#ifndef CTTIME_H
#define CTTIME_H

#include <QDateTime>
#include <QString>
//TODO: NEED MAKE LIKE SINGLTON
class ctTime
{
    quint64 m_prevUpdateTime;
    QDateTime* m_dateTime;
public:
    ctTime();
    ~ctTime();
    //TODO: in future need make to privet an cal by friend method(update) of class ctApp
    void Update(); //need for update delta-time
    quint64 GetMiliSecsSinceEpoch() const;
    QString DateTimeToStr() const;
    quint64 GetDeltaTime() const;
};

#endif // CTTIME_H
