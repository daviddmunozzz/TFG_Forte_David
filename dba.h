#ifndef DBA_H
#define DBA_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDir>
#include <QDebug>
#include <QMutexLocker>


class DBA
{
public:

    static DBA* getInstance();

    bool open();

    bool insert(QString);

    template<typename T>
    QVector<T> select(const QString q);
    bool update();
    bool read();
    bool remove(QString);

private:

    DBA();
    ~DBA();

    QSqlDatabase db;
    QMutex mutex_;

};

template<typename T>
QVector<T> DBA::select(const QString q){
    QSqlQuery query;
    QVector<T> result;

    query.exec(q);

    while (query.next()) {
        result.append(T(query));
    }

    return result;
}

#endif // DBA_H
