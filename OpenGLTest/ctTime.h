#ifndef CTTIME_H
#define CTTIME_H

#include <QDateTime>
#include <QString>
class ctTime
{
private:
//static ctTime* s_instance;
    quint64 m_prevUpdateTime;
    QDateTime* m_dateTime;

    ctTime();
    ctTime(const ctTime & t_time);
    void operator = (ctTime t_time);

public:
    ~ctTime();
    //TODO: in future need make to privet an cal by friend method(update) of class ctApp
    void Update(); //need for update delta-time
    quint64 GetMiliSecsSinceEpoch() const;
    QString DateTimeToStr() const;
    quint64 GetDeltaTime() const;

    static ctTime* GetTime()
    {
        static ctTime* s_instance = 0;
        if(!s_instance)
        {
            s_instance = new ctTime();
        }
        return s_instance;
    }
};

#endif // CTTIME_H
