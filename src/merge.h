#ifndef MERGE_H
#define MERGE_H

#include <QObject>

class Merge : public QObject
{
    Q_OBJECT
public:
    explicit Merge(QObject *parent = nullptr);
    void create();

signals:

public slots:
};

#endif // MERGE_H
