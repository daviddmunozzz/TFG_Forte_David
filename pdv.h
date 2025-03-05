#ifndef PDV_H
#define PDV_H

#include <QChar>
#include <QString>
#include <QObject>
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QSqlQueryModel>


class PDV
{

public:
    PDV(QString PDV_DataDDi, long PDV_DataValue, QString PDT_IdRef, QString VPN_IdRef)
        : PDV_DataDDi_(PDV_DataDDi), PDV_DataValue_(PDV_DataValue),
          PDT_IdRef_(PDT_IdRef), VPN_IdRef_(VPN_IdRef)
    {}

    PDV(const QSqlQuery &query){
        PDV_DataDDi_ = query.value("pdataddi").toString();
        PDV_DataValue_ = query.value("pdatavalue").toInt();

        TZCode_ = query.value("tzcode").toInt();

        PDT_IdRef_ = query.value("pidref").toString();  // probables foreign key
        VPN_IdRef_ = query.value("vpnid").toString();   //

    }

    ~PDV();

    QString getPDVDataDDi() { return PDV_DataDDi_; }
    long getPDVDataValue() { return  PDV_DataValue_; }
    int getTZCode() { return TZCode_; }
    QString getPDTIdRef() { return PDT_IdRef_; }
    QString getVPNIdRef() { return VPN_IdRef_; }


    QString prepareInsert(int8_t);
    static QString prepareSelect();
    QString prepareUpdate();
    QString prepareDelete();

private:
    QString PDV_DataDDi_; //Hex
    long PDV_DataValue_;
    int TZCode_;
    QString PDT_IdRef_;
    QString VPN_IdRef_;
};


#endif // PDV_H
