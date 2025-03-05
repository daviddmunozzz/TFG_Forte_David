#include "task.h"
#include <QDebug>

Task::~Task(){

}
QString Task::prepareInsert(){
    QString q = QString("INSERT INTO task "
                        "VALUES ('%1', '%2')").arg(this->TaskId_).arg(this->PFIdRef_);
    return q;
}


QString Task::prepareSelect(){
    QString q = QString("SELECT * FROM task");

    return q;
}


QString Task::prepareUpdate(QString value, QString change){
   QString q = QString("UPDATE task SET taskId = '%1' WHERE taskId = '%2'").arg(change).arg(value);

   return q;
}

QString Task::prepareDelete(){
    QString q = QString("DELETE FROM task"); /*arg(this->TaskId_);*/

    return q;
}
