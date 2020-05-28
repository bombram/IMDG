    #include "imdgunit.h"

IMDGunit::IMDGunit(){
    imdgUnitData.clear();

}

IMDGunit::IMDGunit(QList<QString> imdgDataReceived){
    imdgUnitData.clear();
    imdgUnitData = imdgDataReceived;


}

IMDGunit::IMDGunit(const IMDGunit &imdgUnitCopy){
  // if (this != &imdgUnitCopy)

        imdgUnitData = imdgUnitCopy.getImdgUnitData();



}

IMDGunit::~IMDGunit(){};


IMDGunit &IMDGunit:: operator=(const IMDGunit &imdgUnit){
    if (this != &imdgUnit){
        imdgUnitData = imdgUnit.getImdgUnitData();
        return *this;
    }
    else return *this;

}


QString IMDGunit::getUnitValueOnTag(const TAGNAME tag) const{

    int startPos = -1;
    int endPos  = -1;

    QString imdgValue;



    for (int index=0;index < imdgUnitData.size();index++){


        if (imdgUnitData.at(index).contains(xmlTags.getTagOpened(tag))) {

            startPos = imdgUnitData.at(index).indexOf(
                        xmlTags.getTagOpened(tag),Qt::CaseInsensitive);
            endPos = imdgUnitData.at(index).indexOf(
                        xmlTags.getTagClosed(tag),startPos,
                                    Qt::CaseInsensitive);

            return imdgUnitData.at(index).mid(
                  (startPos+xmlTags.getTagOpened(tag).length()),
                        (endPos -  (startPos+xmlTags.getTagClosed(tag).length())+1));



        }

    }

    return "-1";


}

QString IMDGunit::getValueOnIndex(int index) const{

    if (index < getItemsQty() )
        return imdgUnitData.at(index);
    else
        return "-1";
}


int IMDGunit::getIndexOnTag(TAGNAME tag) const{

  return imdgUnitData.indexOf(xmlTags.getTagOpened(tag));

}

int IMDGunit::getListIndexOnTag(TAGNAME tag) const{


    for (int index=0;index<imdgUnitData.size();index++){

        if (imdgUnitData.at(index).contains(xmlTags.getTagOpened(tag)))
            return index;
    }

    return -1;


}


QList<QString> IMDGunit::getImdgUnitData() const{
    return imdgUnitData;
}

QString IMDGunit::getDataToString() const{
    QString stringData;

    for (int index=0;index<getItemsQty();index++){
           stringData.append(imdgUnitData.at(index) + "\n");

    }
    return stringData;
}


QString IMDGunit::getDagoID() const{
    return imdgUnitData.at(0);//in IMDG unit DagoID is the fisrt element
}

QString IMDGunit::getDagoEID() const{
    return imdgUnitData.at(EID);
}

QString IMDGunit::getDagoUNNo() const{
    return imdgUnitData.at(4);
}

int IMDGunit::getItemsQty() const{

    return imdgUnitData.size();
}


int IMDGunit::insertValueIntoUnit(QString unitFullLine, TAGNAME whereTagIs){

    int inPos = -1;
    inPos = imdgUnitData.indexOf(xmlTags.getTagOpened(whereTagIs));//to review!!!!!

    if (inPos == -1) return -1;
    else
    {
      imdgUnitData.insert(inPos,unitFullLine);
      return 0;
    }

}

int IMDGunit::inserValueIntoUnit(QString unitFullLine){

    imdgUnitData.push_back(unitFullLine);
    return 1;

}

void IMDGunit::replaceImdgUnit(QList<QString> data){

    imdgUnitData.clear();
    imdgUnitData = data;


}

void IMDGunit::removeAllItems(){

    imdgUnitData.clear();

}

int IMDGunit::setValueOnIndex(int index, QString value){

    if ( index < getItemsQty() ){
        imdgUnitData.replace(index,value);
        return 1;
    }
    else return 0;
}

void IMDGunit::setData(QList<QString> data){

   imdgUnitData = data;
}

bool IMDGunit::isImdgUnitEmpty() const{

    return imdgUnitData.isEmpty();
}


bool IMDGunit::isWeightTagExists() const{

    for (int index = 0; index < imdgUnitData.size(); ++index){
        if (imdgUnitData.at(index).contains(xmlTags.getTagOpened(NetWeight))){
            return true;
        }
    }
    return false;
}







bool IMDGunit::addWeightToIMDGunit(QVector<IMDGunit> &newUnits,  Container &containerDataToInsert,
                                      int unnoCounterRcvd,  bool isNextUnitDifferent){



    QString         tagValue;

    QString         eid, imdgClass, unnoFound, packingGroup,
                    marpol, limitedQuantity, technicalName;
    QList<QString>  imdgNewUnitData;
    IMDGunit        newUnit;
    int             ii = 0;
    bool            ifUNNoFound = false;
    int             index = 0;
    int             classIndex = -1;
    int             pgIndex = -1;
    int             netWeightIndex = -1;
    int             marpolIndex = -1;
    int             limitedQtyIndex = -1;
    bool            ok;
    int             unnoCounter;
    QString         unnoCounterStr;
    TAGNAME         tag = UNNo;
    bool            bugFound = false;

    unnoFound = getUnitValueOnTag(UNNo);
    eid = getUnitValueOnTag(EID);

    QString dagoId,dagoIdTemp;
    //get DagoID from container
    dagoIdTemp = getUnitValueOnTag(DagoID);//get DagoID form container
    dagoIdTemp = dagoIdTemp.mid(0, dagoIdTemp.length() - 3);



    while ( !ifUNNoFound && (!containerDataToInsert.getValueOnIndex(index).contains("</Dago>")) ){
        if (containerDataToInsert.getValueOnIndex(index).contains(unnoFound)){
            classIndex = getListIndexOnTag(Class);
            pgIndex = getListIndexOnTag(PackingGroup);
            netWeightIndex = getListIndexOnTag(NetWeight);
            marpolIndex = getListIndexOnTag(MarPol);
            limitedQtyIndex = getListIndexOnTag(LimitedQuantity);

            if (netWeightIndex > -1){
                setValueOnIndex(netWeightIndex,
                                xmlTags.makeTagValueString(
                                      NetWeight, containerDataToInsert.getValueOnIndex(index + 3)
                                ));


            }else{
                setValueOnIndex(marpolIndex - 1,
                                xmlTags.makeTagValueString(
                                      NetWeight, containerDataToInsert.getValueOnIndex(index + 3)
                                ));

            }


            setValueOnIndex(marpolIndex, xmlTags.makeTagValueString(
                                MarPol, containerDataToInsert.getValueOnIndex(index + 4))
                                );


            if (limitedQtyIndex > -1){
                setValueOnIndex(limitedQtyIndex, xmlTags.makeTagValueString(
                                LimitedQuantity, containerDataToInsert.getValueOnIndex(index + 5))
                                );

            }
            else{
                setValueOnIndex(marpolIndex + 1, xmlTags.makeTagValueString(
                                                LimitedQuantity, containerDataToInsert.getValueOnIndex(index + 5))
                                 );

           }
            unnoCounterStr = containerDataToInsert.getValueOnIndex(5);//take unno counter from container unit
            unnoCounter = unnoCounterStr.toInt(&ok, 10);
            unnoCounter--;
            containerDataToInsert.setValueOnIndex(5, QString::number(unnoCounter));

            for (int indexInner = index; indexInner <= index + 5; ++indexInner ){
                containerDataToInsert.setValueOnIndex(indexInner, "0");
            }
            ifUNNoFound = true;

            /*
             *  Unno is not in manifest we do nothing with it  now. It won't be
             *  written into final cxml file.
             *
             */



        }


        index ++;
    }


   // creating new IMDG units with UNNos taken from Container data(dataToInsert)
    index = 7;

    QRegExp  ifUNNo("[0-9]{4}");

    qDebug()<<"before while"<<"and eid="<<eid;
    if (isNextUnitDifferent){

        while ( unnoCounter > 0){
           // qDebug()<<"before INSIDE" << containerDataToInsert.getValueOnIndex(index) ;
            if ( (containerDataToInsert.getValueOnIndex(index).contains(ifUNNo))){
                qDebug()<<"UNNO===========" <<containerDataToInsert.getValueOnIndex(index);
                //creating new Dago Id using unnoCounter. Every imdg unit has to have Dago ID (for MACS loading Software)
                dagoId = dagoIdTemp;//not to make dagoId longer in the next iterations
                dagoId.append(QString::number(index) + QString::number(index) + QString::number(index));


                //making new Qlist of imdgUnits with minimum fields

                imdgNewUnitData.push_back(xmlTags.makeTagValueString(DagoID, dagoId));
                imdgNewUnitData.push_back(xmlTags.makeTagValueString
                                                  (EID, containerDataToInsert.getValueOnIndex(1) + "new")
                                          );
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString(SubEntry,"0"));
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString
                                                  (Class, containerDataToInsert.getValueOnIndex(index + 1))
                                           );
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString(UNNo, unnoFound));
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString(
                                                   PackingGroup,
                                                   packingGroupToNumber(containerDataToInsert.getValueOnIndex(index + 2))
                                                   )
                                           );
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString(
                                                   NetWeight, containerDataToInsert.getValueOnIndex(index + 3))
                                           );
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString(
                                                   MarPol, containerDataToInsert.getValueOnIndex(index + 4))
                                           );
                 imdgNewUnitData.push_back(xmlTags.makeTagValueString(
                                                   LimitedQuantity, containerDataToInsert.getValueOnIndex(index +5))
                                            );


                //changing continaer unit
                unnoCounter--;
                containerDataToInsert.setValueOnIndex(5, QString::number(unnoCounter));

                //creating new imdg unit
                newUnit.setData(imdgNewUnitData);
                newUnits.push_back(newUnit);
                imdgNewUnitData.clear();
                dagoId.clear();//clear not ot make dagoId longer than it should be
                qDebug()<<"INSIDE";
            }
            index++;
        }
    }//end if isNextUnitDifferent



     return ifUNNoFound;
}




QString IMDGunit::packingGroupToNumber(QString packingGroup){

    if (packingGroup.contains("I")) return "1";
    else{
        if (packingGroup.contains("II")) return "2";
        else{
            if (packingGroup.contains("III")) return "3";
            else return "-";
        }
    }


}
