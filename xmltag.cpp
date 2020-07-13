#include "xmltag.h"

XmlTag::XmlTag()
{
    tagOpening.clear();
    tagClosing.clear();

    for (int index = 0; index < tags.size(); index ++){
       tagOpening.append("<" + tags[index] + ">");
       tagClosing.append( "</" + tags[index] + ">");
    }


}



QString XmlTag::getTagOpened(TAGNAME tag) const{
    return tagOpening.at(tag);

}


QString XmlTag::getTagClosed(TAGNAME tag)const {
    return tagClosing.at(tag);
}

TAGNAME XmlTag::getTagEnumName(int index) const{

    return (tagsEnum.at(index));
}

int XmlTag::getTagSize() const{
    return tags.size();
}


int XmlTag::getTagStringPositions(const QString str, TAGNAME tag, int &endPos){
    int startPos = -1;
    endPos = -1;


    if ( str.contains(getTagOpened(tag)) ){
        startPos = str.indexOf(getTagOpened(tag));
        endPos = str.indexOf(getTagClosed(tag));
        return startPos;
    }
    else return startPos;

}

QString XmlTag::makeTagValueString(TAGNAME tag, QString value){

    return getTagOpened(tag) + value + getTagClosed(tag);

}

int XmlTag::createListTagsValues(TAGNAME[]){


}

//QList<QString> XmlTag::createList(QVector<QString> dataToInsert, TAGNAME from, TAGNAME to){

//    QList<QString> tempList;


//    for (int index = from; index< to; index++){

//        if (dataToInsert.at(index).contains(""))

//        tempList.append( getTagOpened(getTagEnumName(index)) + dataToInsert.at(index) + getTagClosed(getTagEnumName(index)) );

//    }

//    return tempList;



//}





