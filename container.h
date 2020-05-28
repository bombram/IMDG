#ifndef CONTAINER_H
#define CONTAINER_H

#include <QString>
#include <QVector>
#include <QTextEdit>
#include <QList>
#include "xmltag.h"



class Container{


public:


    Container();
    Container(QVector<QString>containerDataReceived);
    Container(const Container &cont);

    ~Container();


     Container & operator=(const Container & cont);

     //getters
     QString getDataToString() const;
     QVector<QString> getContainerData() const;
     QVector<QString> getData() const { return containerData;}
     QString getContainerIdNumber()const;
     QString getValueOnIndex(int index) const;
     QString getContainerEIDNumber()const;
     int getItemsQty() const;

     //setters
     int setValueOnIndex(int index, const QString value);
     void pushBackData(QString value);



     void appendImdgContainerData(QVector<QString> dataReceived);
     void removeAllItems();
     void removeAllItems(int from, int to);




private:


   QVector<QString> containerData;
   XmlTag xmlTags;






};

#endif // CONTAINER_H
