#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QFile>
#include <QXmlStreamReader>

class Map
{

public:
    Map(QString mapID, QString designator, QByteArray tzns,
        QString PFRef, QString gridFile, int gridType)
        : mapID_(mapID), designator_(designator), tzns_(tzns),
          PFRef_(PFRef), gridFile_(gridFile), gridType_(gridType)
    {}

    QString getMapID() { return mapID_; }

    QString getDesignator() { return designator_; }

    long getProcDataVariable() { return procDataVariable_; }

    void setProcDataVariable(long procDataVariable) { procDataVariable_ = procDataVariable; }

    QString getPFRef() { return PFRef_; }

    QString getGridFile() { return gridFile_; }

    int getGridType() { return gridType_; }

    ~Map();

private:
    QString mapID_;
    QString designator_;
    QByteArray tzns_;
   // QString CustomerRef;
    long procDataVariable_;
    QString PFRef_;
    QString gridFile_;
    int gridType_;
};

#endif // MAP_H
