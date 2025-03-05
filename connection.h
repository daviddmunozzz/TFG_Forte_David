#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>

static bool createConnection(QSqlDatabase db)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QDir dir;
    db.setDatabaseName(dir.currentPath()+"/persistence.db");
    if (!db.open()){
        qDebug() << "Cannot open database";
        return false;
    } else {
        qDebug() << "Conexion establecida";
    }

    /*
     * Tablas de bases de datos:
     *          - task --> taskId: Identificador de la tarea
     *                 --> pfidref: Identificador de la parcela ("foreign key")
     *
     *          - tzn --> tzcode: Código de la zona de tratamiento asociado con el mapa de prescripción (grid)
     *                --> taskId: foreign key
     *
     *          - pdv --> pdataddi: Identificador de process data variable
     *                --> tzcode: foreign key
     *                --> pdatavalue: Valor del proceso (cantidad a aplicar en el tipo 1 de lectura del binario)
     *                --> pidref: Referencia del producto que se aplica
     *                --> vpnid'ref'(modificar): Identificador de value presentation. VPN representa la escala, unidad...
     *
     * Conviene reestructurar el código porque en bases de datos no se puede o es complicado almacenar vectores, de esta manera
     * por foreign keys es más fácil la inserción y la extracción de los objetos.
     * ---
     * También se puede mantener el código y transformar. // Opción no recomendable (creo)
     *
     */

    QSqlQuery query;
    if(!query.exec("create table if not exists task ("
               "taskId char(14) primary key,"
               "pfidref char(14) not null"
               ")"))
        qDebug() << "Table task already exists";


    query.exec("create table tzn ("
               "tzcode tinyint unsigned primary key,"
               "taskId char(14),"
               "foreign key (taskId) references task(taskId)"                // Tabla GRD ¿? o elementos en task ¿?
               ")");                                                         // Insertar todos elementos en tabla ¿?

    query.exec("create table pdv ("
               "id long primary key,"
               "pdataddi char(4) not null,"
               "tzcode tinyint,"
               "pdatavalue long not null,"
               "pidref varchar(20) not null,"
               "vpnid varchar(20) not null,"
               "foreign key (tzcode) references tzn(tzcode)"
               ")");

    query.exec("create table grd ("
               "filename varchar(8) primary key,"
               "taskId varchar(14) foreign key,"
               "minNorthPosition float not null,"
               "minEastPosition float not null,"
               "cellNorthSize double not null,"
               "cellEastSize double not null,"
               "maxColumn long not null,"
               "maxRow long not null,"
               "type int not null,"
               "tzcode tinyint,"
               "foreign taskId,"
               "foreign tzcode"  // INCOMPLETO
               ")");



    return true;

}

#endif // CONNECTION_H
