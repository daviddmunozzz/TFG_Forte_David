#ifndef TZN_H
#define TZN_H

#include <QVector>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "pdv.h"

class TZN
{

public:
    TZN(int8_t TZCode) :  TZCode_(TZCode)
    {}

    TZN(const QSqlQuery &query){
        TZCode_ = query.value("tzcode").toInt();
        taskId_ = query.value("taskId").toString();
    }

    ~TZN();

    int8_t getTZCode() { return TZCode_; }
    void setTZCode(int8_t TZCode) { TZCode_ = TZCode; }

    QString getTaskId() { return taskId_; };


    QString prepareInsert(QString taskid);
    static QString prepareSelect();
    QString prepareUpdate();
    QString prepareDelete();


    QVector<PDV*> PDV_Vector;

private:
    int8_t TZCode_;
    QString taskId_;

};




#endif // TZN_H
