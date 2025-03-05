#include "dba.h"
#include "connection.h"
#include "task.h"
#include "tzn.h"
#include "pdv.h"
#include <QMetaType>


DBA::DBA()
{
    if(!db.isOpen()){
        if(!createConnection(db)){
            qDebug() << "Connection failed";
        }
    }
}

bool DBA::read(){
    return true;
}

bool DBA::insert(const QString q){
    QSqlQuery query;
    query.prepare(q);

    return query.exec();
}


bool DBA::update(){
 return true;
}

bool DBA::remove(const QString q){
   QSqlQuery query;
   query.prepare(q);

   query.exec();
   qDebug() << query.lastError();

   return true;
}


DBA* DBA::getInstance(){
    static DBA* instance = nullptr;
    if(instance == nullptr)
        instance = new DBA();

    return instance;
}
