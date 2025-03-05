#include "tzn.h"

TZN::~TZN(){

}

QString TZN::prepareInsert(QString taskid){
    QString q = QString("INSERT INTO tzn "
                        "VALUES ('%1', '%2')").arg(this->TZCode_).arg(taskid);
    return q;
}


QString TZN::prepareSelect(){
    QString q = QString("SELECT * FROM tzn");

    return q;
}

QString TZN::prepareUpdate(){
    QString q = QString("UPDATE tzn SET tzcode = '%1' WHERE tzcode = '%2'"); // args

    return q;
}

QString TZN::prepareDelete(){
    QString q = QString("DELETE FROM tzn"); /* WHERE tzcode = '%1'"*/

    return q;
}
