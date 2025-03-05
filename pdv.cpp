#include "pdv.h"

PDV::~PDV(){

}

QString PDV::prepareInsert(int8_t tzcode){
    QString q = QString("INSERT INTO pdv "
                        "VALUES ('%1', '%2', '%3',"
                        " '%4', '%5', '%6')").arg(QRandomGenerator::global()->generate()     // nº random como id
                        ).arg(this->PDV_DataDDi_
                        ).arg(tzcode).arg(this->PDV_DataValue_).arg(this->PDT_IdRef_).arg(this->VPN_IdRef_);

    return q;
}

QString PDV::prepareSelect(){
    QString q = QString("SELECT * FROM pdv");

    return q;
}

QString PDV::prepareUpdate(){
    QString q = QString("UPDATE pdv SET %1 = %2 WHERE %3 = %4");
    return "";
}

QString PDV::prepareDelete(){
    return "";
}
