#ifndef XMLTAG_H
#define XMLTAG_H

#include <QString>
#include <QVector>

enum TAGNAME{
//group for Container
    Containers = 0,
    EID, Qualifier, IdNumber,  ISOType=4,
//group for IMDG unit
    Dago,
    DagoID,
    EID2, //used as refrence to EID. Only one EID is available for a container
    SubEntry,
    Class,UNNo,
    PackingGroup, NoOfPacking,PackageType,
    NetWeight,MarPol,LimitedQuantity,
    EmS,MFAG,Hazard,
    TechnicalName,
    StowageCategory,
    FlashPointMin,
    Riskzone
};


class XmlTag
{

public:

    XmlTag();
    ~XmlTag(){};


    QString getTagOpened(TAGNAME tag) const;
    QString getTagClosed(TAGNAME tag) const ;
    TAGNAME getTagEnumName(int index) const ;
    int getTagSize() const;
    int getTagStringPositions(const QString str, TAGNAME tag, int &endPpos);
    QList<QString> createList(QVector<QString> dataToInsert, TAGNAME from, TAGNAME to);

    //creates string containing opening tag + value + closing tag
    QString makeTagValueString(TAGNAME tag, QString value);
    int createListTagsValues(TAGNAME[]);






private:

    const QVector<QString> tags = {"Containers",
                                   "EID", "Qualifier", "IdNumber", "ISOType",

                                   "Dago",
                                   "DagoID",
                                   "EID",
                                   "SubEntry",
                                   "Class","UNNo",
                                   "PackingGroup", "NoOfPacking", "PackageType",
                                   "NetWeight", "MarPol", "LimitedQuantity",
                                   "EmS", "MFAG", "Hazard",
                                   "TechnicalName",
                                   "StowageCategory",
                                   "FlashPointMin",
                                   "Riskzone"
                                  };

    const QVector<TAGNAME> tagsEnum = {Containers,
                                       EID,Qualifier,IdNumber,ISOType,

                                       Dago,
                                       DagoID,
                                       EID2,
                                       SubEntry,
                                       Class,UNNo,
                                       PackingGroup, NoOfPacking,PackageType,
                                       NetWeight,MarPol,LimitedQuantity,
                                       EmS,MFAG,Hazard,
                                       TechnicalName,
                                       StowageCategory,
                                       FlashPointMin,
                                       Riskzone
                                       };



    QVector<QString> tagOpening;
    QVector<QString> tagClosing;







};

#endif // XMLTAG_H
