#ifndef SCREENMGR_H
#define SCREENMGR_H

#include <QObject>

class screenmgr : public QObject
{
    Q_OBJECT
public:
    explicit screenmgr(QObject *parent = 0);

signals:

public slots:
};

#endif // SCREENMGR_H
