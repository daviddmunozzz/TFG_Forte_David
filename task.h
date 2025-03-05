#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "tzn.h"

class Task
{

public:

    Task(QString TaskId, QString PFIdRef = "")
        : TaskId_(TaskId), PFIdRef_(PFIdRef)
    {}

    Task(const QSqlQuery &query){
        TaskId_ = query.value("taskid").toString();
        PFIdRef_ = query.value("pfidref").toString();
    }

    ~Task();

    QString getTaskId() { return TaskId_; }
    QString getPFIdRef() { return PFIdRef_; }
    QString getGridFile() { return gridFile_; }
    int getGridType() { return gridType_; }

    void setGridFile(QString gridFile) { gridFile_ = gridFile; }
    void setGridType(int gridType) { gridType_ = gridType; }

    QString prepareInsert();
    static QString prepareSelect();
    QString prepareUpdate(QString, QString);
    QString prepareDelete();

    QVector<TZN*> TZN_Vector;

private:

    QString TaskId_;
    QString PFIdRef_;
    QString gridFile_;
    int gridType_;

};

#endif // TASK_H
